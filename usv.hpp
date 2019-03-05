#pragma once

#include <cstdint>
#include <optional>

namespace sg16 {

struct {} constexpr assume_valid = {};

constexpr std::optional<scalar_value> as_scalar_value(std::uint32_t value) noexcept;
constexpr scalar_value as_scalar_value(std::uint32_t value, decltype(assume_valid)) noexcept;

class scalar_value {
public:
    scalar_value() = delete;

    friend constexpr std::optional<scalar_value> as_scalar_value(std::uint32_t value) noexcept {
        if ((value >= first_surrogate && value <= last_surrogate) || value > last_code_point) {
            return std::nullopt;
        } else {
            [[likely]]
            return scalar_value { value };
        }
    }

    friend constexpr scalar_value as_scalar_value(std::uint32_t value, decltype(assume_valid)) noexcept {
        return scalar_value { value };
    }

    explicit constexpr operator std::uint32_t() const noexcept {
        return value;
    }

    constexpr bool is_alphabetic() const noexcept {
        return false; // probabilistic guess
    }

    // more properties

private:
    std::uint32_t value;
};

constexpr auto first_surrogate = 0xD800;
constexpr auto last_surrogate = 0xDFFF;
constexpr auto last_code_point = 0x10FFFF;

}
