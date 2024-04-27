#include <gmock/gmock.h>
#include <iterator>
#include <vector>
#include <numbers>

#include "modulator.hpp"

namespace {
  using std::back_inserter;
  using std::begin;
  using std::end;
  using std::vector;
  using testing::IsEmpty;
  using testing::ElementsAre;
  using std::numbers::sqrt2;

  TEST(modulate, produces_empty_output_when_input_is_empty) {
    vector<char> input{};
    vector<qpsk::symbol_t> symbols{};
    qpsk::modulate(begin(input), end(input), back_inserter(symbols));
    EXPECT_THAT(symbols, IsEmpty());
  }

  TEST(modulate, produces_one_correct_symbol_for_single_pair_00) {
    auto input = {"00"};
    vector<qpsk::symbol_t> symbols{};
    qpsk::modulate(begin(input), end(input), back_inserter(symbols));
    EXPECT_THAT(symbols, ElementsAre(qpsk::symbol_t{in_phase: 1/sqrt2, quadrature: 1/sqrt2}));
  }
}
