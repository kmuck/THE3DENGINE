export module engine.event:types;

import std;

namespace engine::event {

    // -- Base Events -- //

    export struct AppQuit { };

    // -- Window Events -- //

    export struct WindowClose {
        std::any window = nullptr;
    };

    export struct WindowResize {
        std::any window = nullptr;
        std::uint16_t width = 0;
        std::uint16_t height = 0;
    };

    // -- Events Variant -- //

    export using Event = std::variant<
        AppQuit,
        WindowClose,
        WindowResize
    >;

} // namespace engine::event