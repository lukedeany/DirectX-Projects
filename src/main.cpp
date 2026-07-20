#include <windows.h>
#include <shobjidl.h>
#include <atlbase.h>
#include <d2d1.h>
#include <iostream>
#include <format>

#include "MainWindow.hpp"

#pragma comment(lib, "d2d1.lib")

struct MainState {
    ID2D1Factory            *factory{};
    ID2D1HwndRenderTarget   *pRenderTarget{};
    ID2D1SolidColorBrush    *pBrush{};
    D2D1_ELLIPSE            ellipse{};
};


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int nCmdShow) {
    MainWindow win;

    if (!win.Create(L"Windows App", WS_OVERLAPPEDWINDOW) ) {
        return 0;
    }

    ShowWindow(win.GetWindow(), nCmdShow);

    MSG msg = {};
    while (msg.message != WM_QUIT ) {
        if (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        } else {
            // Updates
        }
    }
}