export module engine.event:types;

import engine.platform;

import std;

namespace engine::event {

    // -- Base Events -- //

    export struct AppQuit { };

    // -- Events Variant -- //

    export using Event = std::variant<
        AppQuit,
        platform::PlatformEvent
    >;

} // namespace engine::event