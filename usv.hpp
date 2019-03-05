#pragma once

#include <cstdint>
#include <optional>

namespace sg16 {

struct {} constexpr assume_valid = {};

class scalar_value {
public:
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

constexpr auto first_surrogate = 0xD800;
constexpr auto last_surrogate = 0xDFFF;
constexpr auto last_code_point = 0x10FFFF;

constexpr std::optional<scalar_value> as_scalar_value(std::uint32_t value) noexcept {
    if ((value >= first_surrogate && value <= last_surrogate) || value > last_code_point) {
        return std::nullopt;
    } else {
        return scalar_value(value, assume_valid);
    }
}

}
