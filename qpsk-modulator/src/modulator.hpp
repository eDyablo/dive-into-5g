#include <ostream>
#include <numbers>
#include <utility>

namespace qpsk {
  struct symbol_t {
    float in_phase;
    float quadrature;

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

    modulator_t(T const& zero): zero(zero) {}

    template <typename I, typename O>
    void modulate(I first, I last, O destination) const {
      using std::numbers::sqrt2;
      if (first != last) {
        symbol_t symbol;
        if (*first == zero) {
          symbol.in_phase = 1/sqrt2;
        } else {
          symbol.in_phase = -1/sqrt2;
        }
        ++first;
        if (*first == zero) {
          symbol.quadrature = 1/sqrt2;
        } else {
          symbol.quadrature = -1/sqrt2;
        }
        *destination = symbol;
      }
    }
  };
}
