module;

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define UNICODE
#include <windows.h>

module engine.platform;

namespace engine::platform {

    const std::wstring wnd_class_name = L"EngineWnd";

    LRESULT CALLBACK WndProc(HWND h, UINT msg, WPARAM wp, LPARAM lp);

    struct Host::WindowData {
        HWND hwnd;
    };

    Host::Host() {
        WNDCLASSEXW wc {
            .cbSize        = sizeof(wc),
            .style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
            .lpfnWndProc   = &WndProc,
            .cbClsExtra    = 0,
            .cbWndExtra    = 0,
            .hInstance     = ::GetModuleHandleW(nullptr),
            .hIcon         = ::LoadIconW(nullptr, IDI_APPLICATION),
            .hCursor       = ::LoadCursorW(nullptr, IDC_ARROW),
            .hbrBackground = reinterpret_cast<HBRUSH>((COLOR_WINDOW + 1)),
            .lpszMenuName  = nullptr,
            .lpszClassName = wnd_class_name.c_str(),
            .hIconSm       = ::LoadIconW(nullptr, IDI_APPLICATION)
        };

        ::RegisterClassExW(&wc);
    };

    Host::~Host() {
        for (auto& window : windows_)
            if (window.has_value())
                ::DestroyWindow(window.value().hwnd);

        ::UnregisterClassW(wnd_class_name.c_str(), ::GetModuleHandleW(nullptr));
    }

    std::expected<WID, std::string> Host::create_window(std::uint16_t width, std::uint16_t height, std::string_view title) {
        int size_needed = ::MultiByteToWideChar(CP_UTF8, 0, title.data(), static_cast<int>(title.size()), nullptr, 0);
        std::wstring wtitle(size_needed, 0);
        ::MultiByteToWideChar(CP_UTF8, 0, title.data(), static_cast<int>(title.size()), wtitle.data(), size_needed);

        RECT r { 0, 0, width, height };
        ::AdjustWindowRectEx(&r, WS_OVERLAPPEDWINDOW, FALSE, 0);

        HWND hwnd = ::CreateWindowExW(
            0,
            wnd_class_name.c_str(),
            wtitle.c_str(),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            r.right - r.left,
            r.bottom - r.top,
            nullptr,
            nullptr,
            ::GetModuleHandleW(nullptr),
            nullptr
        );

        if (!hwnd)
            return std::unexpected("Failed to create window");

        ::ShowWindow(hwnd, SW_SHOWNORMAL);

        windows_.push_back(
            WindowData {
                .hwnd = hwnd
            }
        );

        return windows_.size() - 1;
    }

    std::expected<void, std::string> Host::destroy_window(WID wid) {
        if (wid >= windows_.size())
            return std::unexpected("Invalid window ID");

        if (!windows_[wid].has_value())
            return std::unexpected("Window already destroyed");

        ::DestroyWindow(windows_[wid].value().hwnd);
        windows_[wid] = std::nullopt;
        return {};
    }
}