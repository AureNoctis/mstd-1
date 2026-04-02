#include "mstd_gfx.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#pragma comment(lib, "User32")
#pragma comment(lib, "gdi32")

LRESULT CALLBACK win32_window_callback(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    return DefWindowProc(window, message, wParam, lParam);
}

function void gfx_init(GFXContext* ctx, GFXFlag flags) {
    if(ctx && ctx->is_initialized)
        return;

    ctx->instance.val[0] = (u64)GetModuleHandle(NULL);

    WNDCLASSA win_class = {0};
    win_class.style = CS_VREDRAW | CS_HREDRAW;
    win_class.lpfnWndProc = win32_window_callback;
    win_class.hInstance = (HINSTANCE)ctx->instance.val[0];
    win_class.lpszClassName = "mstd_app";

    ctx->is_initialized = 1;
    ctx->init_flags = flags;

    if(!RegisterClassA(&win_class))
        ctx = 0;
}

function void gfx_window_create(GFXContext* ctx, Str8 name, u32 width, u32 height) {
    debug_validate(ctx);
    debug_validate(ctx->is_initialized);

    HWND window = CreateWindowExA(
        0,
        (char*)"mstd_app", (char*)name.data,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT,
        width ? width : CW_USEDEFAULT, height ? height : CW_USEDEFAULT,
        0, 0, (HINSTANCE)ctx->instance.val[0], 0
    );

    if(window)
        ctx->window.val[0] = (u64)window;
}

function void gfx_poll_events(GFXContext* ctx, u32 peek) {
    debug_validate(ctx);
    debug_validate(ctx->is_initialized);

    MSG message;
    if (peek) {
        while (PeekMessageA(&message, 0, 0, 0, 0)) {
            TranslateMessage(&message);
            DispatchMessageA(&message);
        }
    }
    else {
        while (GetMessageA(&message, 0, 0, 0)) {
            TranslateMessage(&message);
            DispatchMessageA(&message);
        }
    }
}
