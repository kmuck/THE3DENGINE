export module engine.runtime:config;

import std;

namespace engine::runtime {

    export class Config {
    public:
        static Config from_file(const std::filesystem::path& path) {

            return Config{};
        }
    };

} // namespace engine