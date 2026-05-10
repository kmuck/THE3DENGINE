export module engine.ecs:component;

import engine.math;

import std;

namespace engine::ecs {

    export struct Transform {
        math::Vector<float,3> position;
        math::Quaternion<float> rotation;
        math::Vector<float,3> scale;
    };

    export struct Camera {
        float fov = 60.f;
        float aspect_ratio = 16.f / 9.f;
        float near_clip = 0.1f;
        float far_clip = 1000.f;
    };

    export using Component = std::variant<
        Transform,
        Camera
    >;

    export using Signature = std::bitset<std::variant_size_v<Component>>;

} // namespace engine::ecs