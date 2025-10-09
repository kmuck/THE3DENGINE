export module engine.ecs:system;

import :registry;

import std;

namespace engine::ecs {

    export class System {
    public:
        System() = default;
        virtual ~System() = default;

        virtual void update(Registry& registry, std::chrono::steady_clock::duration dt) = 0;
    };

}