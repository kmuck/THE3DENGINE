export module engine.graphics;

import engine.ecs;

import std;

namespace engine::graphics {

    export class Renderer final : public ecs::System {
    public:
        Renderer() = default;
        ~Renderer() override = default;

        void update(ecs::Registry& registry, std::chrono::steady_clock::duration dt) override {

            // std::cout << "Rendering frame, dt: " << dt.count() << "s\n";

        }

    };

}
