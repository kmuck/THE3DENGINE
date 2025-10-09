module engine.platform;

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define UNICODE
#include <windows.h>

import std;

namespace engine::platform {

    struct Slot {
        HWND hwnd = nullptr;
        std::uint32_t version = 1;
    };

    static std::vector<Slot> windows;
    static std::vector<std::uint32_t> free_indexes;

    static std::queue<Event> events;

    static bool valid(WindowHandle handle) {
        return handle.index() < windows.size() && handle.version() == windows[handle.index()].version;
    }

    static WindowHandle hwnd_to_handle(HWND h) {
        if (!h) return {0, 0};
        auto idx = static_cast<std::uint32_t>(::GetWindowLongPtrW(h, GWLP_USERDATA));
        if (idx >= windows.size()) return {0, 0};
        return WindowHandle{ idx, windows[idx].version };
    }

    static std::wstring utf8_to_utf16(const std::string_view s) {
        if (s.empty()) return {};
        int n = ::MultiByteToWideChar(CP_UTF8, 0, s.data(), static_cast<int>(s.size()), nullptr, 0);
        std::wstring w(n, 0);
        ::MultiByteToWideChar(CP_UTF8, 0, s.data(), static_cast<int>(s.size()), w.data(), n);
        return w;
    }

    static LRESULT CALLBACK WndProc(HWND h, UINT msg, WPARAM wp, LPARAM lp) {
        switch (msg) {
            case WM_NCCREATE: {
                auto cs  = reinterpret_cast<CREATESTRUCTW*>(lp);
                auto idx = static_cast<std::uint32_t>(reinterpret_cast<uintptr_t>(cs->lpCreateParams));
                ::SetWindowLongPtrW(h, GWLP_USERDATA, static_cast<LONG_PTR>(idx));
                return ::DefWindowProcW(h, msg, wp, lp);
            }
            case WM_SIZE: {
                events.push(Event {
                    .type = Event::Type::WindowResized,
                    .window = hwnd_to_handle(h),
                    .size = {
                        .width = LOWORD(lp),
                        .height = HIWORD(lp)
                    }});
                return ::DefWindowProcW(h, msg, wp, lp);
            }
            case WM_KEYDOWN: {
                events.push(Event {
                .type = Event::Type::KeyDown,
                    .window = hwnd_to_handle(h),
                    .key = {
                        .key = static_cast<int>(wp),
                        .repeat = (lp & (1 << 30)) != 0
                    }});
                return ::DefWindowProcW(h, msg, wp, lp);
            }
            case WM_DESTROY: {
                const auto idx = static_cast<std::uint32_t>(::GetWindowLongPtrW(h, GWLP_USERDATA));
                windows[idx].hwnd = nullptr;
                windows[idx].version += 1;
                free_indexes.push_back(idx);
                return ::DefWindowProcW(h, msg, wp, lp);
            }
            default:
                return ::DefWindowProcW(h, msg, wp, lp);
        }
    }

    static ATOM ensure_class_registered() {
        static ATOM atom = 0;
        if (atom) return atom;

        WNDCLASSEXW wc {
            .cbSize        = sizeof(wc),
            .style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
            .lpfnWndProc   = &WndProc,
            .hInstance     = ::GetModuleHandleW(nullptr),
            .hIcon         = ::LoadIconW(nullptr, IDI_APPLICATION),
            .hCursor       = ::LoadCursorW(nullptr, IDC_ARROW),
            .lpszClassName = L"EngineWnd",
            .hIconSm       = ::LoadIconW(nullptr, IDI_APPLICATION)
            // .hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
        };

        atom = ::RegisterClassExW(&wc);
        return atom;
    }

    WindowHandle create_window(int width, int height, std::string_view title) {

        std::uint32_t index = 0;
        std::uint32_t version = 0;

        if (!free_indexes.empty()) {
            index = free_indexes.back();
            free_indexes.pop_back();
            windows[index].hwnd = nullptr;
            version = windows[index].version;
        } else {
            index = static_cast<std::uint32_t>(windows.size());
            version = 1;
            windows.push_back(Slot{});
        }

        RECT r { 0, 0, width, height };
        ::AdjustWindowRectEx(&r, WS_OVERLAPPEDWINDOW, FALSE, 0);

        auto hwnd = ::CreateWindowExW(
            0,
            MAKEINTATOM(ensure_class_registered()),
            utf8_to_utf16(title).c_str(),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            r.right - r.left,
            r.bottom - r.top,
            nullptr,
            nullptr,
            ::GetModuleHandleW(nullptr),
            reinterpret_cast<LPVOID>(static_cast<uintptr_t>(index))
        );

        if (!hwnd) throw std::runtime_error("Failed to create window");

        windows[index].hwnd = hwnd;

        ::ShowWindow(hwnd, SW_SHOW);
        ::UpdateWindow(hwnd);
        return WindowHandle{ index, version };
    }

    void destroy_window(WindowHandle handle) {
        if (!valid(handle)) return;
        ::DestroyWindow(windows[handle.index()].hwnd);
    }

    void show_window(WindowHandle handle) {
        if (!valid(handle)) return;
        ::ShowWindow(windows[handle.index()].hwnd, SW_SHOW);
    }

    void hide_window(WindowHandle handle) {
        if (!valid(handle)) return;
        ::ShowWindow(windows[handle.index()].hwnd, SW_HIDE);
    }

    void pump_events() {
        MSG msg;
        while (::PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                events.push(Event{ .type = Event::Type::Quit, .window = WindowHandle(0, 0) });
            } else {
                ::TranslateMessage(&msg);
                ::DispatchMessageW(&msg);
            }
        }
    }

    std::optional<Event> poll_event() {
        if (events.empty()) return std::nullopt;

        Event ev = std::move(events.front());
        events.pop();
        return ev;
    }

} // namespace engine::platform