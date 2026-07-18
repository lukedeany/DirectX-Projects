#include <windows.h>
#include <shobjidl.h>
#include <atlbase.h>
#include <d2d1.h>
#include <iostream>
#include <format>

#pragma comment(lib, "d2d1.lib")

struct MainState {
    ID2D1Factory            *factory{};
    ID2D1HwndRenderTarget   *pRenderTarget{};
    ID2D1SolidColorBrush    *pBrush{};
    D2D1_ELLIPSE            ellipse{};
};


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
    const TCHAR CLASS_NAME[] = TEXT("Window Class");

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    auto *pState = new MainState;

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        TEXT("Programming on Windows"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        nullptr,
        nullptr,
        hInstance,
        pState
    );

    ShowWindow(hwnd, nCmdShow);


    MSG msg = {};
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    delete pState;

    return 0;
}

LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    MainState *pState;

    if (uMsg == WM_NCCREATE) {
        auto *pCreate = reinterpret_cast<CREATESTRUCT *>(lParam);
        pState = static_cast<MainState *>(pCreate->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pState));
    } else {
        LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
        pState = reinterpret_cast<MainState *>(ptr);
    }

    switch (uMsg) {
        case WM_CREATE: {
            if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pState->factory))) {
                return -1;
            }

            return 0;
        }

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            FillRect(hdc, &ps.rcPaint, reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1));

            EndPaint(hwnd, &ps);

            OutputDebugString(TEXT("Print!\n"));

            return 0;
        }
        case WM_DESTROY:
            PostQuitMessage(0);

            //std::cout << std::format("%d draw calls\n", pState->ticks);
            return 0;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}