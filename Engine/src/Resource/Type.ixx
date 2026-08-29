export module engine.resource:type;

import engine.math;

import std;

namespace engine::resource {

    export using RID = std::size_t;

    enum class SerializationError { FileNotFound, CorruptedData };

    export struct Resource {
        virtual ~Resource() = default;
        virtual std::expected<void, SerializationError> serialize(std::ostream& stream) const = 0;
        virtual std::expected<void, SerializationError> deserialize(std::istream& stream) = 0;
    };

    export struct Mesh final : Resource {

        struct Vertex {
            math::Vector<float, 3> position;
            math::Vector<float, 3> normal;
            math::Vector<float, 2> tex_coord;
        };

        using Indice = std::size_t;

        std::vector<Vertex> vertices;
        std::vector<Indice> indices;

        std::expected<void, SerializationError> serialize(std::ostream &stream) const override {
            return {};
        }

        std::expected<void, SerializationError> deserialize(std::istream &stream) override {
            return {};
        }

    };

} // namespace engine::resource