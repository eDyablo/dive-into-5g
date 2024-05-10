#pragma once

#include "symbol.hpp"

namespace qpsk {
  template <typename T>
  struct demodulator_t {
    T const zero;
    T const one;

    demodulator_t(T const& zero, T const& one): zero(zero), one(one) {}

    template <typename I>
    struct output_iterator_t {
      demodulator_t& demodulator;
      I destination;

      explicit output_iterator_t(demodulator_t& demodulator, I destination):
        demodulator(demodulator), destination(destination) {
      }

      output_iterator_t& operator++() {
        return *this;
      }

      output_iterator_t& operator++(int) {
        return *this;
      }

      output_iterator_t& operator=(symbol_t const& value) {
        if (value.is_valid()) {
          *destination++ = value.in_phase > 0 ? demodulator.zero : demodulator.one;
          *destination++ = value.quadrature > 0 ? demodulator.zero : demodulator.one;
        }
        return *this;
      }

      output_iterator_t& operator*() {
        return *this;
      }
    };

    template <typename I>
    auto iterator(I destination) {
      return output_iterator_t{*this, destination};
    }
  };
}
