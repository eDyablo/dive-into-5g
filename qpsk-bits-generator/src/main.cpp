#include <iostream>
#include <ranges>

#include "options.hpp"

namespace {
  using std::array;
  using std::ranges::contains;
  using std::views::join;
  using std::views::repeat;
  using std::views::transform;

  template<typename R>
  void emit_bits(R&& range) {
    auto constexpr zero = '0';
    auto constexpr unit = '1';
    auto constexpr to_bit = [](auto item) {
      constexpr auto zero_symbols = array{'0', ' '};
      return contains(zero_symbols, item) ? zero : unit;
    };
    for (auto const bit : range | transform(to_bit)) {
      std::cout << bit;
    }
  }

  void emit_finite_bits_sequence(options_t options) {
    emit_bits(repeat(options.pattern(), options.repetition_count()) | join);
  }

  void emit_infinite_bits_sequence(options_t const& options) {
    emit_bits(repeat(options.pattern()) | join);
  }
}

int main(int argc, char const* argv[]) {
  auto const options = options_t{argc, argv};
  if (options.finite_repetition()) {
    emit_finite_bits_sequence(options);
  } else if (options.infinite_repetition()){
    emit_infinite_bits_sequence(options);
  }
}
