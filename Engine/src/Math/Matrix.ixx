export module engine.math:matrix;

import std;

namespace engine::math {

    export template<typename T, size_t Rows, size_t Cols>
    requires std::is_arithmetic_v<T>
    class Matrix {
    public:
        Matrix() {}

    private:
        std::array<T, Rows*Cols> data_;
    };

} // namespace engine::math