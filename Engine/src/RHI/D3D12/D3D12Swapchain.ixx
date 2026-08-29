module;

#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>

export module engine.rhi.d3d12:swapchain;

import engine.rhi;

namespace engine::rhi {

    export class D3D12Swapchain : public Swapchain {
    public:
        D3D12Swapchain() {

        }

        ~D3D12Swapchain() override {

        }
    };

}