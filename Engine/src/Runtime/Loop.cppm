export module engine.runtime:loop;

import :context;
import :scheduler;

import engine.platform;

import std;

namespace engine::runtime {

    export class Loop {
    public:
        explicit Loop(Scheduler& scheduler) : scheduler_(scheduler) {}
        ~Loop() = default;

        void run() {

            // -- Init --
            running = true;
            auto last = std::chrono::steady_clock::now();

            // -- Main Loop --
            while (running) {

                // -- Time Step --
                auto start = std::chrono::steady_clock::now();
                const auto dt = start - last;
                last = start;

                // -- Step --
                this->step(dt);

                // -- Frame Cap --
                while (std::chrono::steady_clock::now() < start + target_frame_time)
                    std::this_thread::yield();
            }
        }


        void step(std::chrono::steady_clock::duration dt) {

            platform::pump_events();
            while (auto ev = platform::poll_event()) {
                if (ev->type == platform::Event::Type::KeyDown && ev->key.key == 27)
                    running = false;
            }

            while (accumulator_ >= target_fixed_time) {

                scheduler_.run(Phase::PreFixed, registry_, target_fixed_time);
                scheduler_.run(Phase::Fixed, registry_, target_fixed_time);
                scheduler_.run(Phase::PostFixed, registry_, target_fixed_time);

                accumulator_ -= target_fixed_time;
            }

            scheduler_.run(Phase::PreUpdate, registry_, dt);
            scheduler_.run(Phase::Update, registry_, dt);
            scheduler_.run(Phase::PostUpdate, registry_, dt);

            scheduler_.run(Phase::PreRender, registry_, dt);
            scheduler_.run(Phase::Render, registry_, dt);
            scheduler_.run(Phase::PostRender, registry_, dt);

        }

    private:
        Scheduler& scheduler_;
        ecs::Registry registry_;

        bool running = false;

        std::chrono::milliseconds target_fixed_time = std::chrono::milliseconds(16);
        std::chrono::milliseconds target_frame_time = std::chrono::milliseconds(16);

        std::chrono::steady_clock::duration accumulator_ = std::chrono::steady_clock::duration::zero();
        std::chrono::steady_clock::duration max_accumulator_ = std::chrono::steady_clock::duration(std::chrono::milliseconds(250));
    };

} // namespace engine