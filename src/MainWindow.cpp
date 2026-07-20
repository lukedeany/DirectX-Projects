//
// Created by datae on 7/19/2026.
//

#include "MainWindow.hpp"

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT: {
            MainWindow::OnPrint(uMsg, wParam, lParam);
        }
    }

    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
;
}

void MainWindow::OnPrint(UINT uMsg, WPARAM wParam, LPARAM lParam) {

}

MainWindow::MainWindow() {

}
