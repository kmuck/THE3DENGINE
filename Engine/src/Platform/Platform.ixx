export module engine.platform;

import std;

namespace engine::platform {

    // --- Window --- //

    class WindowHandle {
    public:
        constexpr WindowHandle(std::uint32_t idx, std::uint32_t ver) : value(static_cast<std::uint64_t>(ver) << 32 |
                                                                             static_cast<std::uint64_t>(idx)) {}

        [[nodiscard]] constexpr std::uint32_t index() const noexcept {
            return static_cast<std::uint32_t>(value & 0xFFFFFFFFull);
        }
        [[nodiscard]] constexpr std::uint32_t version() const noexcept {
            return static_cast<std::uint32_t>(value >> 32);
        }

        auto operator<=>(const WindowHandle&) const = default;

    private:
        std::uint64_t value = 0;
    };

    export WindowHandle create_window(int width, int height, std::string_view title);
    export void destroy_window(WindowHandle handle);

    export void show_window(WindowHandle handle);
    export void hide_window(WindowHandle handle);

    // export void set_window_title(WindowHandle handle, std::string_view title);
    // export void set_window_size(WindowHandle handle, int width, int height);
    //
    // export [[nodiscard]] std::string get_window_title(WindowHandle handle);
    // export [[nodiscard]] std::pair<int, int> get_window_size(WindowHandle handle);

    // --- Event --- //

    export struct Event {
        enum class Type {
            Quit,
            WindowResized,
            KeyDown, KeyUp,
            MouseMove, MouseDown, MouseUp,
            MouseWheel
        } type = Type::Quit;
        WindowHandle window;
        union {
            struct { int width, height; } size;
            struct { int key; bool repeat; } key;
            struct { int x, y; int dx, dy; } mouse;
            struct { float x, y; } scroll;
        };
    };

    export void pump_events();
    export std::optional<Event> poll_event();

    // --- Render --- //


} // namespace engine::platform