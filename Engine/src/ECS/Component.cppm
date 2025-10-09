export module engine.ecs:component;

namespace engine::ecs {

    export class Component {
    public:
        Component() = default;
        virtual ~Component() = default;
    };

}