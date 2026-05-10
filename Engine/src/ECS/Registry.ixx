export module engine.ecs:registry;

import :entity;
import :component;
import :archetype;

import std;

namespace engine::ecs {

    export class Registry {
    public:
        Registry() = default;

        // template<typename... Components>
        // std::tuple<std::span<Components>...> view();

    private:
        std::unordered_map<Signature, IArchetype> archetypes_;
    };

} // nnamespace engine::ecs