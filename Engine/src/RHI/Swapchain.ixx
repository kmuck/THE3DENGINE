export module engine.rhi:swapchain;

import std;

namespace engine::rhi {

    export class Swapchain  {
    public:
        virtual ~Swapchain() = default;

        virtual void present() = 0;
    };

}