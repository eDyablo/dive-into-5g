#include <gmock/gmock.h>
#include <iterator>
#include <numbers>
#include <ranges>
#include <string>
#include <tuple>
#include <vector>

#include "modulator.hpp"

namespace {
  using qpsk::modulator_t;
  using qpsk::symbol_t;
  using std::back_inserter;
  using std::begin;
  using std::end;
  using std::make_tuple;
  using std::numbers::sqrt2;
  using std::string;
  using std::tuple;
  using std::vector;
  using std::views::repeat;
  using testing::Each;
  using testing::ElementsAre;
  using testing::ElementsAreArray;
  using testing::IsEmpty;
  using testing::SizeIs;
  using testing::Test;
  using testing::Values;
  using testing::WithParamInterface;

  struct modulation : public Test {
    modulator_t<char> modulator{'0', '1'};
    vector<symbol_t> symbols{};
  };

  TEST_F(modulation, produces_empty_output_when_input_is_empty) {
    vector<char> input{};
    modulator.modulate(begin(input), end(input), back_inserter(symbols));
    EXPECT_THAT(symbols, IsEmpty());
  }

  struct giving_sequence_and_expected_symbols : public modulation,
    public WithParamInterface<tuple<string, vector<symbol_t>>> {
  };

  TEST_P(giving_sequence_and_expected_symbols, produces_correct_symbols) {
    auto [input, expected] = GetParam();
    modulator.modulate(begin(input), end(input), back_inserter(symbols));
    EXPECT_THAT(symbols, ElementsAreArray(expected));
  }

  INSTANTIATE_TEST_CASE_P(modulation, giving_sequence_and_expected_symbols, Values(
    make_tuple("00", vector{symbol_t{in_phase: 1/sqrt2, quadrature: 1/sqrt2}}),
    make_tuple("01", vector{symbol_t{in_phase: 1/sqrt2, quadrature: -1/sqrt2}}),
    make_tuple("10", vector{symbol_t{in_phase: -1/sqrt2, quadrature: 1/sqrt2}}),
    make_tuple("0", vector<symbol_t>{}),
    make_tuple("1", vector<symbol_t>{}),
    make_tuple("0011", vector{
      symbol_t{in_phase: 1/sqrt2, quadrature: 1/sqrt2},
      symbol_t{in_phase: -1/sqrt2, quadrature: -1/sqrt2},
    }),
    make_tuple("00011011", vector{
      symbol_t{in_phase: 1/sqrt2, quadrature: 1/sqrt2},
      symbol_t{in_phase: 1/sqrt2, quadrature: -1/sqrt2},
      symbol_t{in_phase: -1/sqrt2, quadrature: 1/sqrt2},
      symbol_t{in_phase: -1/sqrt2, quadrature: -1/sqrt2},
    }),
    make_tuple("000", vector{symbol_t{in_phase: 1/sqrt2, quadrature: 1/sqrt2}}),
    make_tuple("001", vector{symbol_t{in_phase: 1/sqrt2, quadrature: 1/sqrt2}}),
    make_tuple("a0", vector<symbol_t>{}),
    make_tuple("a1", vector<symbol_t>{}),
    make_tuple("0b", vector<symbol_t>{}),
    make_tuple("1b", vector<symbol_t>{}),
    make_tuple("ab", vector<symbol_t>{}),
    make_tuple("00a0", vector{symbol_t{in_phase: 1/sqrt2, quadrature: 1/sqrt2}}),
    make_tuple("01a1", vector{symbol_t{in_phase: 1/sqrt2, quadrature: -1/sqrt2}}),
    make_tuple("100b", vector{symbol_t{in_phase: -1/sqrt2, quadrature: 1/sqrt2}}),
    make_tuple("111b", vector{symbol_t{in_phase: -1/sqrt2, quadrature: -1/sqrt2}}),
    make_tuple("11ab", vector{symbol_t{in_phase: -1/sqrt2, quadrature: -1/sqrt2}}),
    make_tuple("01ab10", vector{
      symbol_t{in_phase: 1/sqrt2, quadrature: -1/sqrt2},
      symbol_t{in_phase: -1/sqrt2, quadrature: 1/sqrt2},
    }),
    make_tuple("00a1010b10ab11", vector{
      symbol_t{in_phase: 1/sqrt2, quadrature: 1/sqrt2},
      symbol_t{in_phase: 1/sqrt2, quadrature: -1/sqrt2},
      symbol_t{in_phase: -1/sqrt2, quadrature: 1/sqrt2},
      symbol_t{in_phase: -1/sqrt2, quadrature: -1/sqrt2},
    })
  ));

  TEST_F(modulation, a_big_sequence_of_repeated_one_bits) {
    auto const input_size = 1'000'000;
    auto const input = repeat('1', input_size);
    modulator.modulate(begin(input), end(input), back_inserter(symbols));
    EXPECT_THAT(symbols, SizeIs(input_size/2));
    EXPECT_THAT(symbols, Each(symbol_t{in_phase: -1/sqrt2, quadrature: -1/sqrt2}));
  }

  TEST_F(modulation, overwrites_destination_symbols) {
    auto const input = {'0', '1', '1', '0'};
    auto output = vector{symbol_t{}, symbol_t{}};
    modulator.modulate(begin(input), end(input), begin(output));
    EXPECT_THAT(output, ElementsAre(
      symbol_t{in_phase: 1/sqrt2, quadrature: -1/sqrt2},
      symbol_t{in_phase: -1/sqrt2, quadrature: 1/sqrt2}));
  }
}
