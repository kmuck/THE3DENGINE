import engine.platform;
import engine.graphics;
import engine.event;
import engine.log;

import std;

int main(int argc, char* argv[]) try {

    // -- Init System -- //
    engine::event::Bus bus;
    // engine::scene::Director director;

    auto device = engine::platform::make_device(engine::platform::GfxApi::D3D12);
    if (!device)
        engine::log::fatal("Failed to create device: {}", device.error());

    engine::graphics::Renderer renderer(*device.value());

    // bus.subscribe(renderer.on_window_create);
    // bus.subscribe(renderer.on_window_close);

    // bus.subscribe<engine::platform::WindowResize>([&renderer](const engine::platform::WindowResize& event) {
    //     renderer.on_window_resize(event);
    // });

    auto window = engine::platform::Host::get().create_window(800, 600, "Engine");
    if (!window)
        engine::log::fatal("Failed to create window");

    // -- Init Clock -- //
    auto fixed_step = std::chrono::nanoseconds(16'666'667);
    auto frame_cap  = std::chrono::nanoseconds(16'666'667);

    auto accumulator = std::chrono::nanoseconds::zero();
    auto last_update = std::chrono::steady_clock::now();

    // -- Game Loop -- //
    auto running = true;
    while (running)
    {
        // -- Scene Check -- //
        // if (director.hasPending()) director.loadPending( store );

        // -- Clock Tock -- //
        auto start_time = std::chrono::steady_clock::now();;
        auto delta_time = start_time - last_update;
        last_update += delta_time;
        accumulator += delta_time;

        // -- Event Loop -- //
        engine::platform::pump_events();
        for (auto event : engine::platform::poll_events())
            bus.queue(event);
        engine::platform::clear_events();

        bus.dispatch();

        // -- Fixed Step -- //
        auto max_steps = 5;
        while (accumulator > fixed_step && max_steps-- > 0)
        {
            // world.simulate(fixed_step);

            // engine::log::info("fixed step");

            accumulator -= fixed_step;
        }

        // // -- Variable Step -- //
        // renderer.begin_frame();
        // renderer.draw(
        //     director.active().view<Transform, Camera>(),
        //     director.active().view<Transform, MeshRenderer>(),
        //     director.active().view<Transform, Light>()
        // );
        // renderer.end_frame();

        // -- Frame Cap -- //
        while (std::chrono::steady_clock::now() - start_time < frame_cap)
            std::this_thread::yield();

        engine::log::flush();
    }

} catch (const std::exception &e) {
    engine::log::fatal("Unhandled exception: {}", e.what());
}