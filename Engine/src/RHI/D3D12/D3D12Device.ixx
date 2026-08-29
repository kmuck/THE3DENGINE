module;

#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>

export module engine.rhi.d3d12:device;

import engine.rhi;

namespace engine::rhi {

    export class D3D12Device : public Device {
    public:
        D3D12Device() {

        }

        ~D3D12Device() override {

        }

    private:
        Microsoft::WRL::ComPtr<ID3D12Device> device_;
    };

}