#include <gmock/gmock.h>

#include "demodulator.hpp"

#include <algorithm>
#include <numbers>
#include <ranges>
#include <tuple>
#include <vector>

namespace {
  using qpsk::demodulator_t;
  using qpsk::symbol_t;
  using std::begin;
  using std::copy;
  using std::end;
  using std::make_tuple;
  using std::numbers::sqrt2;
  using std::ostream_iterator;
  using std::string;
  using std::stringstream;
  using std::tuple;
  using std::vector;
  using std::views::repeat;
  using testing::Each;
  using testing::ElementsAre;
  using testing::Eq;
  using testing::IsEmpty;
  using testing::SizeIs;
  using testing::Test;
  using testing::Values;
  using testing::WithParamInterface;

  struct demodulation : public Test {
    demodulator_t<char> demodulator{'0', '1'};
    stringstream output;

    template <typename R>
    auto demodulated(R range) {
      copy(begin(range), end(range),
      demodulator.iterator(ostream_iterator<char>(output)));
      return output.str();
    }
  };

  TEST_F(demodulation, produces_empty_output_when_input_is_empty) {
    auto const input = vector<symbol_t>{};
    EXPECT_THAT(demodulated(input), IsEmpty());
  }

  struct giving_symbols_and_expected_sequence : public demodulation,
    public WithParamInterface<tuple<symbol_t, string>> {
  };

  TEST_P(giving_symbols_and_expected_sequence, produces_correct_pair_of_bits) {
    auto [input, expected] = GetParam();
    EXPECT_THAT(demodulated(std::vector{input}), Eq(expected));
  }

  INSTANTIATE_TEST_CASE_P(demodulation, giving_symbols_and_expected_sequence, Values(
    make_tuple(symbol_t{in_phase: 1/sqrt2, quadrature: 1/sqrt2}, "00"),
    make_tuple(symbol_t{in_phase: 1/sqrt2, quadrature: -1/sqrt2}, "01"),
    make_tuple(symbol_t{in_phase: -1/sqrt2, quadrature: 1/sqrt2}, "10"),
    make_tuple(symbol_t{in_phase: -1/sqrt2, quadrature: -1/sqrt2}, "11"),
    make_tuple(symbol_t{in_phase: 0.1, quadrature: 0.01}, "00"),
    make_tuple(symbol_t{in_phase: 0.001, quadrature: -0.0001}, "01"),
    make_tuple(symbol_t{in_phase: -1, quadrature: 10}, "10"),
    make_tuple(symbol_t{in_phase: -100, quadrature: -1000}, "11")
  ));

  struct giving_single_symbol : public demodulation,
    public WithParamInterface<symbol_t> {
  };

  TEST_P(giving_single_symbol, produces_empty_sequence) {
    auto const symbol = GetParam();
    EXPECT_THAT(demodulated(std::vector{symbol}), IsEmpty());
  }

  INSTANTIATE_TEST_CASE_P(demodulation, giving_single_symbol, Values(
      symbol_t{in_phase: 0, quadrature: 1/sqrt2},
      symbol_t{in_phase: 1/sqrt2, quadrature: 0},
      symbol_t{in_phase: 0, quadrature: 0},
      symbol_t{}
  ));

  TEST_F(demodulation, overwrites_destination_bits) {
    auto const source = vector{
      symbol_t{in_phase: 1/sqrt2, quadrature: 1/sqrt2},
      symbol_t{in_phase: 1/sqrt2, quadrature: -1/sqrt2},
      symbol_t{in_phase: -1/sqrt2, quadrature: 1/sqrt2},
      symbol_t{in_phase: -1/sqrt2, quadrature: -1/sqrt2},
    };
    auto destination = vector<char>{'1', '1', '1', '0', '0', '1', '0', '0' };
    copy(begin(source), end(source), demodulator.iterator(begin(destination)));
    EXPECT_THAT(destination, ElementsAre('0', '0', '0', '1', '1', '0', '1', '1'));
  }

  TEST_F(demodulation, a_big_sequence_of_repeated_symbols) {
    auto const amount = 1'000'000;
    auto const symbol = symbol_t{in_phase: -1/sqrt2, quadrature: -1/sqrt2};
    auto const symbols = repeat(symbol, amount);
    auto bits = vector<char>{};
    copy(begin(symbols), end(symbols), demodulator.iterator(back_inserter(bits)));
    EXPECT_THAT(bits, SizeIs(amount * 2));
    EXPECT_THAT(bits, Each(Eq('1')));
  }
}
