export module engine.ecs:archetype;

import :entity;
import :component;

import std;

namespace engine::ecs {

    struct IArchetype {
        virtual ~IArchetype() = default;
    };

    template<typename... Component>
    struct Archetype : IArchetype {
        std::vector<EID> entities_;
        std::tuple<std::vector<Component>...> components_;
    };

} // namespace engine::ecs

