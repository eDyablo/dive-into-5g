#pragma once

#include <cmath>
#include <random>

#include "qpsk/snr.hpp"
#include "qpsk/symbol.hpp"

namespace qpsk {
  struct noise_injector_t {
    std::random_device rd;
    std::minstd_rand gen;
    std::normal_distribution<float> distr;

    noise_injector_t(snr_t snr): rd{}, gen{rd()},
      distr{0.0, 1 / snr.linear()} {
    }

    auto make_noise() {
      return distr(gen);
    }

    auto add_noise(symbol_t const& source) {
      return symbol_t{
        in_phase: source.in_phase + make_noise(),
        quadrature: source.quadrature + make_noise()
      };
    }

    template <typename I>
    struct output_iterator_t {
      noise_injector_t& injector;
      I destination;

      explicit output_iterator_t(noise_injector_t& injector, I destination):
        injector(injector), destination(destination) {
      }

      output_iterator_t& operator++() {
        return *this;
      }

      output_iterator_t& operator++(int) {
        return *this;
      }

      output_iterator_t& operator=(symbol_t const& source) {
        *destination++ = injector.add_noise(source);
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
