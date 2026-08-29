export module engine.log;

import std;

namespace engine::log {

    inline constexpr bool DEBUG = true;

    export void flush() {
        std::cout << std::flush;
    }

    export template<typename... Args>
    void info(std::string_view fmt, Args&&... args) {
        if constexpr (!DEBUG) return;
        std::cout << "[INFO] " << std::vformat(fmt, std::make_format_args(args...)) << "\n";
    }

    export template<typename... Args>
    void warn(std::string_view fmt, Args&&... args) {
        if constexpr (!DEBUG) return;
        std::cout << "[WARNING] " << std::vformat(fmt, std::make_format_args(args...)) << "\n";
    }

    export template<typename... Args>
    void error(std::string_view fmt, Args&&... args) {
        if constexpr (!DEBUG) return;
        std::cout << "[ERROR] " << std::vformat(fmt, std::make_format_args(args...)) << "\n";
    }

    export template<typename... Args>
    void fatal(std::string_view fmt, Args&&... args) {
        if constexpr (!DEBUG) return;
        std::cout << "[FATAL] " << std::vformat(fmt, std::make_format_args(args...)) << std::flush;
        std::exit(-1);
    }

} // namespace engine::log