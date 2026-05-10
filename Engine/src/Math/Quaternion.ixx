export module engine.math:quaternion;

import std;

namespace engine::math {

    export template<typename T>
    requires std::is_arithmetic_v<T>
    class Quaternion {
    public:
        Quaternion() {}

        T& operator[](size_t index) { return data_[index]; }
        const T& operator[](size_t index) const { return data_[index]; }

    private:
        std::array<T, 4> data_;
    };

} // namespace engine::math