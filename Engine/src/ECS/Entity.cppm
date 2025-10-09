export module engine.ecs:entity;

import std;

namespace engine::ecs {

    export using EID = std::uint32_t;

    export constexpr EID INVALID_EID = 0;

}