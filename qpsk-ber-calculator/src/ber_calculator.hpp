#include <iomanip>
#include <limits>
#include <ostream>
#include <ranges>
#include <vector>

namespace qpsk {
  struct error_rate_t {
    size_t const errors;
    size_t const total;

    operator float() const {
      return static_cast<float>(errors) / total;
    }

    auto percentage() const {
      return static_cast<unsigned int>((100 * errors) / total);
    }
  };

  struct percentage_error_rate_t {
    error_rate_t raw;

    percentage_error_rate_t(error_rate_t&& rate) : raw(std::move(rate)) {
    }

    friend std::ostream& operator<<(std::ostream& output,
        percentage_error_rate_t const& rate) {
      auto const percentage = rate.raw.percentage();
      auto const errors = rate.raw.errors;
      if (percentage < 1 and errors > 0) {
        return output << percentage << '%' << errors;
      } else {
        return output << percentage << '%';
      }
    }
  };

  struct ber_calculator_t {
    template <typename S1, typename S2, typename R>
    void compute(S1&& subject_sequence, S2&& sampling_sequence, R rates,
        size_t interval=std::numeric_limits<size_t>::max()) {
      auto bit_count = size_t{0};
      auto error_count = size_t{0};
      auto sampling_iter = std::begin(sampling_sequence);
      for (auto subject_iter = std::begin(subject_sequence);
          subject_iter != std::end(subject_sequence)
            and sampling_iter != std::end(sampling_sequence);
          ++subject_iter, ++sampling_iter) {
        auto const subject_bit = *subject_iter;
        auto const sample_bit = *sampling_iter;
        if (sample_bit != subject_bit) {
          ++error_count;
        }
        if (++bit_count == interval) {
          *rates = error_rate_t{error_count, bit_count};
          bit_count = 0;
          error_count = 0;
        }
      }
      for (; sampling_iter != std::end(sampling_sequence); ++sampling_iter) {
        ++error_count;
        if (++bit_count == interval) {
          *rates = error_rate_t{error_count, bit_count};
          bit_count = 0;
          error_count = 0;
        }
      }
      if (bit_count) {
        *rates = error_rate_t{error_count, bit_count};
      }
    }

    template <typename S1, typename S2>
    auto rates(S1&& subject_sequence, S2&& sampling_sequence,
        size_t interval=std::numeric_limits<size_t>::max()) {
      auto rates = std::vector<error_rate_t>{};
      compute(subject_sequence, sampling_sequence, std::back_inserter(rates), interval);
      return rates;
    }
  };
}
