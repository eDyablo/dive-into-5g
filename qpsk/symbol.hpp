#pragma once

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
      return output << "(I" << symbol.in_phase << ",Q" << symbol.quadrature << ")";
    }
  };
}
