import engine.platform;
import engine.event;
import engine.log;

import std;

int main(int argc, char* argv[]) try {

    // -- Init System -- //
    engine::event::Bus bus;
    engine::platform::Host host;
    // engine::scene::Director director;
    // engine::graphics::Renderer renderer(host, store);

    auto wid1 = host.create_window(800, 600, "Engine");
    if (!wid1)
        engine::log::error("Failed to create window: {}", wid1.error());

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
            bus.enqueue(event);

        bus.dispatch();

        // -- Fixed Step -- //
        while (accumulator > fixed_step)
        {
            // world.simulate(fixed_step);

            // std::println("fixed step");

            accumulator -= fixed_step;
        }

        // -- Variable Step -- //
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