module engine.platform;

import engine.rhi;
import engine.rhi.d3d12;
// import engine.rhi.vulkan;

namespace engine::platform {

    std::expected<std::unique_ptr<rhi::Device>, std::string> make_device(GfxApi api) {
        switch (api) {
            case GfxApi::D3D12:
                return std::make_unique<rhi::D3D12Device>();
            // case GfxApi::Vulkan:
            //     return std::make_unique<rhi::VulkanDevice>();
            default:
                return std::unexpected("Unsupported graphics API");
        }
    }
}