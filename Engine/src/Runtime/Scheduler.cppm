export module engine.runtime:scheduler;

import engine.ecs;

import std;

namespace engine::runtime {

    export enum class Phase {
        PreFixed, Fixed, PostFixed,
        PreUpdate, Update, PostUpdate,
        PreRender, Render, PostRender,
        Count
    };

    export class Scheduler {
    public:
        template <typename T, typename... Args>
        requires std::is_base_of_v<ecs::System, T>
        void enqueue(Phase phase, Args&&... args) {
            systems_.at(static_cast<size_t>(phase)).emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
        }

        void run(Phase phase, ecs::Registry& registry, const std::chrono::steady_clock::duration dt) const {
            for (const auto& system : systems_.at(static_cast<size_t>(phase))) {
                system->update(registry, dt);
            }
        }

    private:
        std::array<std::vector<std::unique_ptr<ecs::System>>, static_cast<size_t>(Phase::Count)> systems_;
    };

} // namespace engine