#pragma once

#include <ostream>
#include <numbers>

#include "qpsk/symbol.hpp"

namespace qpsk {
  template <typename T>
  struct modulator_t {
    T const zero;
    T const one;

    modulator_t(T const& zero, T const& one): zero(zero), one(one) {}

    template <typename I, typename O>
    void modulate(I first, I last, O destination) const {
      for (; first != last; ++first) {
        symbol_t symbol;
        symbol.in_phase = modulate(*first);
        if (++first == last)
          break;
        symbol.quadrature = modulate(*first);
        if (symbol.is_valid()) {
          *destination++ = symbol;
        }
      }
    }

    auto modulate(T const bit) const {
      using std::numbers::sqrt2;
      if (bit == zero) {
        return 1/sqrt2;
      } else if (bit == one) {
        return -1/sqrt2;
      } else {
        return decltype(1/sqrt2){};
      }
    }
  };
}
