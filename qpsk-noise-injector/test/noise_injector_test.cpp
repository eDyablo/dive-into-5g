#include <gmock/gmock.h>

#include "noise_injector.hpp"

#include <algorithm>
#include <cmath>
#include <ranges>
#include <vector>

namespace {
  using namespace qpsk::literals;
  using qpsk::noise_injector_t;
  using qpsk::snr_t;
  using qpsk::symbol_t;
  using std::back_inserter;
  using std::begin;
  using std::end;
  using std::vector;
  using std::views::repeat;
  using testing::Eq;
  using testing::IsEmpty;
  using testing::Ne;
  using testing::Pointwise;
  using testing::SizeIs;
  using testing::Test;

  struct noise_injection : public Test {
    noise_injector_t injector;

    noise_injection(snr_t snr = 20_dB): injector{snr} {
    }

    template <typename R>
    auto add_noise(R range) {
      auto distorted_symbols = vector<symbol_t>{};
      copy(begin(range), end(range), injector.iterator(back_inserter(distorted_symbols)));
      return distorted_symbols;
    }
  };

  TEST_F(noise_injection, produces_empty_sequence_when_source_is_empty) {
    EXPECT_THAT(add_noise(vector<symbol_t>{}), IsEmpty());
  }

  TEST_F(noise_injection, produces_the_same_amount_of_symbols_as_the_source_provides) {
    EXPECT_THAT(add_noise(repeat(symbol_t{}, 10)), SizeIs(10));
  }

  TEST_F(noise_injection, distores_each_symbol_taken_from_the_source) {
    auto const basic_symbols = vector<symbol_t>{{1, 2}, {-3, 4}, {5, -6}, {-7,-8}};
    auto seq = std::views::repeat(basic_symbols) | std::views::take(10000) | std::views::join;
    auto const source = vector<symbol_t>{begin(seq), end(seq)};
    EXPECT_THAT(add_noise(source), Ne(source));
  }

  struct very_low_noise : public noise_injection {
    very_low_noise(): noise_injection{50_dB} {
    }
  };

  MATCHER_P(SymbolNear, max_absolute_error, "very close") {
    using std::abs;
    auto const [first, second] = arg;
    return abs(first.in_phase - second.in_phase) <= max_absolute_error
      and abs(first.quadrature - second.quadrature) <= max_absolute_error;
  }

  TEST_F(very_low_noise, does_not_affect_signal_clearleness) {
    auto const basic_symbols = vector<symbol_t>{{0.1, 0.1}, {-0.1, 0.1}, {0.1, -0.1}, {-0.1,-0.1}};
    auto seq = std::views::repeat(basic_symbols) | std::views::take(10000) | std::views::join;
    auto const source = vector<symbol_t>{begin(seq), end(seq)};
    EXPECT_THAT(add_noise(source), Pointwise(SymbolNear(1e-4), source));
  }

  TEST_F(noise_injection, overwrites_destination) {
    auto const source = vector{10, symbol_t{1, -1}};
    auto destination = source;
    copy(begin(source), end(source), injector.iterator(begin(destination)));
    EXPECT_THAT(destination, Pointwise(Ne(), source));
  }
}
