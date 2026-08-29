export module engine.platform:host;

import :event;

import std;

namespace engine::platform {

    export class Host {
    public:
        Host(const Host&) = delete;
        Host& operator=(const Host&) = delete;
        Host(Host&&) = delete;
        Host& operator=(Host&&) = delete;

        static Host& get() {
            static Host instance;
            return instance;
        }

        std::expected<WID, std::string> create_window(
            std::uint16_t width,
            std::uint16_t height,
            std::string_view title
        );

        std::expected<void, std::string> destroy_window(WID wid);

    private:
        struct WindowData;
        std::vector<std::optional<WindowData>> windows_;

        Host();
        ~Host();
    };

}