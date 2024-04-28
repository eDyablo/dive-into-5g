#include <ostream>
#include <numbers>
#include <utility>

namespace qpsk {
  struct symbol_t {
    float in_phase;
    float quadrature;

    bool is_valid() const {
      return in_phase != 0 and quadrature != 0;
    }

    bool operator==(symbol_t const& rhs) const {
      return in_phase == rhs.in_phase and quadrature == rhs.quadrature;
    }

    friend std::ostream& operator<<(std::ostream& output, symbol_t const& symbol) {
      return output << "(I" << symbol.in_phase << ", Q" << symbol.quadrature << ")";
    }
  };

  template <typename T>
  struct modulator_t {
    T const zero;
    T const one;

    modulator_t(T const& zero, T const& one): zero(zero), one(one) {}

    template <typename I, typename O>
    void modulate(I first, I last, O destination) const {
      using std::numbers::sqrt2;
      for (; first != last; ++first) {
        symbol_t symbol;
        symbol.in_phase = modulate(*first);
        if (++first == last)
          break;
        symbol.quadrature = modulate(*first);
        if (symbol.is_valid()) {
          *destination = symbol;
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
