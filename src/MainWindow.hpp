#ifndef WINDOWSTEST_MAINWINDOW_HPP
#define WINDOWSTEST_MAINWINDOW_HPP
#include <d3d11.h>
#include <d3dcommon.h>

#include "Window.hpp"

class MainWindow : public Window<MainWindow> {
public:
    LPCWSTR ClassName() const { return L"Sample Window Class"; }

    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

    void OnPrint(UINT uMsg, WPARAM wParam, LPARAM lParam);

    MainWindow();

    void Render() override;

    HRESULT CreateDevice();

private:
    D3D_DRIVER_TYPE m_driverType {D3D_DRIVER_TYPE_NULL};
    ID3D11Device* m_pd3dDevice;
    ID3D11DeviceContext* m_pImmediateContext;
    D3D_FEATURE_LEVEL m_featureLevel {D3D_FEATURE_LEVEL_11_0};
};

#endif //WINDOWSTEST_MAINWINDOW_HPP
