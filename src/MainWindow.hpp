#ifndef WINDOWSTEST_MAINWINDOW_HPP
#define WINDOWSTEST_MAINWINDOW_HPP
#include "Window.hpp"

class MainWindow : public Window<MainWindow> {
public:
    LPCWSTR ClassName() const { return L"Sample Window Class"; }

    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

    void OnPrint(UINT uMsg, WPARAM wParam, LPARAM lParam);

    MainWindow();
};

#endif //WINDOWSTEST_MAINWINDOW_HPP
