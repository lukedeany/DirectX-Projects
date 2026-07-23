#include "MainWindow.hpp"
#include <d3d11_1.h>

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT: {
            MainWindow::OnPrint(uMsg, wParam, lParam);
        }
    }

    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);;
}

void MainWindow::OnPrint(UINT uMsg, WPARAM wParam, LPARAM lParam) {
}

void MainWindow::Render() {

}

HRESULT MainWindow::CreateDevice() {
    HRESULT hr = S_OK;

    RECT rc;
    GetClientRect( m_hwnd, &rc );
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    UINT createDeviceFlags = 0;

    D3D_DRIVER_TYPE driverTypes[] =
        {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };

    UINT numDriverTypes = ARRAYSIZE ( driverTypes );

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
    UINT numFeaturesLevels = ARRAYSIZE( featureLevels );

    for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++) {
        m_driverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDevice(nullptr, m_driverType, nullptr, createDeviceFlags, featureLevels, numFeaturesLevels,
            D3D11_SDK_VERSION, &m_pd3dDevice, &m_featureLevel, &m_pImmediateContext);

        if (hr == E_INVALIDARG) {
            hr = D3D11CreateDevice(nullptr, m_driverType, nullptr, createDeviceFlags, &featureLevels[1], numFeaturesLevels - 1,
                D3D11_SDK_VERSION, &m_pd3dDevice, &m_featureLevel, &m_pImmediateContext);
        }

        if (SUCCEEDED(hr)) {
            break;
        }
    }

    if (FAILED(hr)) {
        return hr;
    }

    IDXGIFactory1* dxgiFactory = nullptr;
    {
        IDXGIDevice* dxgiDevice = nullptr;
        hr = m_pd3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));

        if (SUCCEEDED(hr)) {
            IDXGIAdapter* adapter = nullptr;
            hr = dxgiDevice->GetAdapter(&adapter);
            if (SUCCEEDED(hr)) {
                hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory));
                adapter->Release();
            }

            dxgiDevice->Release();
        }
    }

    if (FAILED(hr)) {
        return hr;
    }

}

MainWindow::MainWindow() {
}
