#pragma once

#include <cstdint>

namespace sg16 {

constexpr auto first_surrogate = 0xD800;
constexpr auto last_surrogate = 0xDFFF;
constexpr auto last_code_point = 0x10FFFF;

struct {} constexpr bad_scalar_value = {};
struct {} constexpr assume_valid = {};

class scalar_value {
public:
    explicit constexpr scalar_value(std::uint32_t value)
    : value(value) {
        if ((value >= first_surrogate && value <= last_surrogate) || value > last_code_point) {
            throw bad_scalar_value;
        }
    }

    explicit constexpr scalar_value(std::uint32_t value, decltype(assume_valid)) noexcept
    : value(value) {}

    explicit constexpr operator std::uint32_t() const noexcept {
        return value;
    }

    constexpr bool is_alphabetic() const noexcept {
        return false; // TODO
    }

    // more properties

private:
    std::uint32_t value;
};

}
