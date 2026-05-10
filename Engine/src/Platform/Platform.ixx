export module engine.platform;

import engine.event;

import std;

namespace engine::platform {

    using WID = std::size_t;

    struct Window;

    export class Host {
    public:
        Host();
        ~Host();

        // -- Window -- //
        std::expected<WID, std::string> create_window(int width, int height, const std::string& title);
        void destroy_window(WID wid);

        // void show_window(WID wid);
        // void hide_window(WID wid);
        //
        // void set_window_title(WID wid, const std::string& title);
        // void set_window_size(WID wid, int width, int height);

        // [[nodiscard]] std::string get_window_title(WID wid);
        // [[nodiscard]] std::pair<int, int> get_window_size(WID wid);

        // [[nodiscard]] NativeHandle native_window_handle(WID wid);

        // -- Input -- //
        // bool is_key_pressed(WID wid, KeyCode key);
        // bool is_key_released(WID wid, KeyCode key);
        //
        // std::pair<int, int> mouse_position(WID wid);

    private:
        std::vector<std::optional<Window>> windows_;
    };

    export void pump_events();
    export std::span<const event::Event> poll_events();

} // namespace engine::platform