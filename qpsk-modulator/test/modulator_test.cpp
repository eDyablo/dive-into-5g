#include <gmock/gmock.h>
#include <iterator>
#include <numbers>
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
  using testing::ElementsAreArray;
  using testing::IsEmpty;
  using testing::Test;
  using testing::Values;
  using testing::WithParamInterface;

  struct modulate : public Test {
    modulator_t<char> modulator{'0'};
    vector<symbol_t> symbols{};
  };

  TEST_F(modulate, produces_empty_output_when_input_is_empty) {
    vector<char> input{};
    modulator.modulate(begin(input), end(input), back_inserter(symbols));
    EXPECT_THAT(symbols, IsEmpty());
  }

  struct modulate_sequence : public modulate,
    public WithParamInterface<tuple<string, vector<symbol_t>>> {
  };

  TEST_P(modulate_sequence, produces_correct_symbols) {
    auto [input, expected] = GetParam();
    modulator.modulate(begin(input), end(input), back_inserter(symbols));
    EXPECT_THAT(symbols, ElementsAreArray(expected));
  }

  INSTANTIATE_TEST_CASE_P(for_a_single_pair, modulate_sequence, Values(
    make_tuple("00", vector{symbol_t{in_phase: 1/sqrt2, quadrature: 1/sqrt2}}),
    make_tuple("01", vector{symbol_t{in_phase: 1/sqrt2, quadrature: -1/sqrt2}}),
    make_tuple("10", vector{symbol_t{in_phase: -1/sqrt2, quadrature: 1/sqrt2}})
  ));

  INSTANTIATE_TEST_CASE_P(for_a_single_bit, modulate_sequence, Values(
    make_tuple("0", vector<symbol_t>{}),
    make_tuple("1", vector<symbol_t>{})
  ));

  INSTANTIATE_TEST_CASE_P(for_multiple_bit_pairs, modulate_sequence, Values(
    make_tuple("0011", vector{
      symbol_t{in_phase: 1/sqrt2, quadrature: 1/sqrt2},
      symbol_t{in_phase: -1/sqrt2, quadrature: -1/sqrt2},
    })
  ));
}
