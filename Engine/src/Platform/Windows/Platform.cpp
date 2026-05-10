module;

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define UNICODE
#include <windows.h>

module engine.platform;

import engine.log;

import std;

namespace engine::platform {

    struct Window {
        HWND h;
    };

    const std::wstring wnd_class_name = L"EngineWnd";

    static std::vector<event::Event> queue_;

    static LRESULT CALLBACK WndProc(HWND h, UINT msg, WPARAM wp, LPARAM lp) {
        switch (msg) {
            case WM_DESTROY:
                ::PostQuitMessage(0);
                queue_.push_back( event::AppQuit { } );
                return 0;
            case WM_CLOSE:
                ::DestroyWindow(h);
                queue_.push_back( event::WindowClose {
                    .window = h
                });
                return 0;
            case WM_SIZE:
                queue_.push_back( event::WindowResize {
                    .window = h,
                    .width  = LOWORD(lp),
                    .height = HIWORD(lp)
                });
                return 0;
            default:
                return ::DefWindowProcW(h, msg, wp, lp);
        }
    }

    void pump_events() {
        queue_.clear();

        MSG msg;
        while (::PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
            ::TranslateMessage(&msg);
            ::DispatchMessageW(&msg);
        }
    }

    std::span<const event::Event> poll_events() {
        return queue_;
    }

    Host::Host() {
        // -- Register Window Class -- //
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
    }

    Host::~Host() {
        for (auto& window : windows_)
            if (window) ::DestroyWindow(window.value().h);

        ::UnregisterClassW(wnd_class_name.c_str(), ::GetModuleHandleW(nullptr));
    }

    std::expected<WID, std::string> Host::create_window(int width, int height, const std::string& title) try {

        int size_needed = MultiByteToWideChar(CP_UTF8, 0, title.data(), static_cast<int>(title.size()), nullptr, 0);
        std::wstring wtitle(size_needed, 0);
        MultiByteToWideChar(CP_UTF8, 0, title.data(), static_cast<int>(title.size()), wtitle.data(), size_needed);

        RECT r { 0, 0, width, height };
        ::AdjustWindowRectEx(&r, WS_OVERLAPPEDWINDOW, FALSE, 0);

        HWND hwnd = ::CreateWindowExW(
            0,
            L"EngineWnd", // MAKEINTATOM(...),
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

        if (!hwnd) throw std::runtime_error("Failed to create window");

        ::ShowWindow(hwnd, SW_SHOWNORMAL);

        windows_.emplace_back( Window {
            .h = hwnd,
        });
        return windows_.size() - 1;

    } catch (const std::exception& e) {
        return std::unexpected(e.what());
    }

    void Host::destroy_window(WID wid) {
        if (wid >= windows_.size() || !windows_[wid]) return;
        ::DestroyWindow(windows_[wid].value().h);
        windows_[wid].reset();
    }

} // namespace engine::platform