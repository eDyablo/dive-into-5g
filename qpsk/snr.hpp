#pragma once

namespace qpsk {
  struct snr_t {
    float relative = 0;

    constexpr float linear() const noexcept {
      return std::pow(10, relative / 10);
    }
  };

  namespace literals {
    constexpr snr_t operator""_dB(long double arg) noexcept {
      return snr_t{relative: static_cast<decltype(snr_t::relative)>(arg)};
    }

    constexpr snr_t operator""_dB(unsigned long long arg) noexcept {
      return snr_t{relative: static_cast<decltype(snr_t::relative)>(arg)};
    }
  }
}
