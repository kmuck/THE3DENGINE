export module engine.platform:render;

import engine.rhi;

import std;

namespace engine::platform {

    export enum class GfxApi {
        D3D12,
        Vulkan
    };

    export std::expected<std::unique_ptr<rhi::Device>, std::string> make_device(GfxApi api);

}