module;

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define UNICODE
#include <windows.h>

module engine.platform;

namespace engine::platform {

    std::vector<PlatformEvent> g_event_queue;

    void pump_events() {
        MSG msg;
        while (::PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                return ;

            ::TranslateMessage(&msg);
            ::DispatchMessageW(&msg);
        }
    }

    std::span<PlatformEvent> poll_events() {
        return g_event_queue;
    }

    void clear_events() {
        g_event_queue.clear();
    }

    LRESULT CALLBACK WndProc(HWND h, UINT msg, WPARAM wp, LPARAM lp) {
        switch (msg) {
            case WM_CLOSE:
                g_event_queue.push_back(WindowClose{
                    .id = 0
                });
                break;
            case WM_SIZE:
                g_event_queue.push_back(WindowResize{
                    .id = 0,
                    .width = LOWORD(lp),
                    .height = HIWORD(lp)
                });
                break;
            default:
                break;
        }
        return ::DefWindowProcW(h, msg, wp, lp);
    }

}