export module engine.graphics:renderer;

import engine.resource;
import engine.platform;
import engine.rhi;

import std;

namespace engine::graphics {

    export class Renderer {
    public:
        explicit Renderer(rhi::Device& device) : device_(device) {

        }

        ~Renderer() = default;

        void begin_frame() {
            // // Prepare for rendering a new frame
            // for (auto& swapchain : swapchains_)
            //     swapchain->acquire_next_image();
        }

        void draw() {
            // // Record rendering commands and submit them to the GPU
            // auto command_list = device_.create_command_list();
            // command_list->begin();
            // // ... rendering commands ...
            // command_list->end();
            // device_.submit_command_list(command_list.get());
        }

        void end_frame() {
            // Present the rendered image to the screen
            for (auto& swapchain : swapchains_)
                swapchain.present();
        }

        void on_window_create(const platform::WindowCreate& event);
        void on_window_close(const platform::WindowClose& event);
        void on_window_resize(const platform::WindowResize& event);

    private:
        rhi::Device& device_;
        std::vector<rhi::Swapchain> swapchains_;
        // std::unordered_map<resource::RID, rhi::Buffer> buffers_;
    };

}