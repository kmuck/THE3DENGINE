export module engine.platform:event;

import :types;
import std;

namespace engine::platform {

    export struct WindowCreate {
        WID id;
    };

    export struct WindowClose {
        WID id;
    };

    export struct WindowResize {
        WID id;
        std::uint16_t width;
        std::uint16_t height;
    };

    export using PlatformEvent = std::variant<
        WindowCreate,
        WindowClose,
        WindowResize
    >;

    export void pump_events();
    export std::span<PlatformEvent> poll_events();
    export void clear_events();

} // namespace engine::platform