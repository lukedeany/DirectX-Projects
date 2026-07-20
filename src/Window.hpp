//
// Created by datae on 7/19/2026.
//

#ifndef WINDOWSTEST_WINDOW_HPP
#define WINDOWSTEST_WINDOW_HPP
#include <D2DBaseTypes.h>

template <class DERIVED_TYPE>
class Window {
public:
    virtual ~Window() = default;

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        DERIVED_TYPE *pThis = nullptr;

        if (uMsg == WM_NCCREATE) {
            auto *pCreate = reinterpret_cast<CREATESTRUCT *>(lParam);
            pThis = static_cast<DERIVED_TYPE *>(pCreate->lpCreateParams);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));

            pThis->m_hwnd = hwnd;
        } else {
            LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
            pThis = reinterpret_cast<DERIVED_TYPE *>(ptr);
        }

        if (pThis) {
            return pThis->HandleMessage(uMsg, wParam, lParam);
        }
        else {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    Window() : m_hwnd(nullptr) {}

    BOOL Create(
        LPCWSTR lpWindowName,
        DWORD dwStyle,
        DWORD dwExStyle = 0,
        int x = CW_USEDEFAULT,
        int y = CW_USEDEFAULT,
        int nWidth = CW_USEDEFAULT,
        int nHeight = CW_USEDEFAULT,
        HWND hWndParent = nullptr,
        HMENU hMenu = nullptr
        ) {
        WNDCLASSW wc = {0};

        wc.lpfnWndProc      = DERIVED_TYPE::WindowProc;
        wc.hInstance        = GetModuleHandle(nullptr);
        wc.lpszClassName    = ClassName();

        RegisterClassW(&wc);

        m_hwnd = CreateWindowExW(dwExStyle, ClassName(), lpWindowName, dwStyle, x,y,nWidth,nHeight,hWndParent,hMenu,GetModuleHandle(nullptr), this);

        return (m_hwnd ? TRUE : FALSE);
    }

    HWND GetWindow() const {return m_hwnd;}


protected:

    virtual LPCWSTR ClassName() const = 0;
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

    HWND m_hwnd;
};

#endif //WINDOWSTEST_WINDOW_HPP
