export module engine.math:vector;

import std;

namespace engine::math {

    export template<typename T, std::size_t size>
    requires std::is_arithmetic_v<T>
    class Vector {
    public:
        Vector() = default;
        ~Vector() = default;

        T& operator[](std::size_t index) { return data_[index]; }
        const T& operator[](std::size_t index) const { return data_[index]; }

        T& at(std::size_t index) {
            if (index >= size) throw std::out_of_range("Index out of range");
            return data_[index];
        }
        const T& at(std::size_t index) const {
            if (index >= size) throw std::out_of_range("Index out of range");
            return data_[index];
        }

        // static constexpr std::size_t size() { return size; }

        friend std::ostream& operator<<(std::ostream& os, const Vector<T, size>& vec) {
            os << "[";
            for (std::size_t i = 0; i < size; ++i) {
                os << vec[i];
                if (i < size - 1) os << ", ";
            }
            os << "]";
            return os;
        }

    private:
        std::array<T, size> data_;
    };

} // namespace engine::math