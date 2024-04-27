#include <ostream>
#include <numbers>

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
 
  template <typename I, typename O>
  void modulate(I first, I last, O destination) {
    using std::numbers::sqrt2;
    if (first != last) {
      *destination = symbol_t{in_phase: 1/sqrt2, quadrature: 1/sqrt2};
    }
  }
}
