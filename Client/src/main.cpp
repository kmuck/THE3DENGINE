import engine.runtime;
import engine.graphics;

import engine.platform;

import std;

using namespace engine;

int main(int argc, char* argv[]) try
{
    runtime::Config config = runtime::Config::from_file("config.toml");

    runtime::Scheduler scheduler;

    scheduler.enqueue<graphics::Renderer>(runtime::Phase::Render);

    runtime::Loop loop(scheduler);

    loop.run();

    return 0;

} catch (const std::exception &e) {
    std::cerr << "Unhandled exception: " << e.what() << std::endl;
    return 1;
}