#include <gmock/gmock.h>
#include <iterator>
#include <numbers>
#include <string>
#include <tuple>
#include <vector>

#include "modulator.hpp"

namespace {
  using std::back_inserter;
  using std::begin;
  using std::end;
  using std::make_tuple;
  using std::numbers::sqrt2;
  using std::string;
  using std::tuple;
  using std::vector;
  using testing::ElementsAre;
  using testing::IsEmpty;
  using testing::Test;
  using testing::TestWithParam;
  using testing::Values;

  TEST(modulate, produces_empty_output_when_input_is_empty) {
    vector<char> input{};
    vector<qpsk::symbol_t> symbols{};
    qpsk::modulate(begin(input), end(input), back_inserter(symbols));
    EXPECT_THAT(symbols, IsEmpty());
  }

  struct single_pair : public TestWithParam<tuple<string, qpsk::symbol_t>> {
    qpsk::modulator_t<char> modulator = qpsk::modulator_t('0');
    vector<qpsk::symbol_t> symbols = {};
  };

  TEST_P(single_pair, produces_correct_symbol) {
    auto [input, expected] = GetParam();
    modulator.modulate(begin(input), end(input), back_inserter(symbols));
    EXPECT_THAT(symbols, ElementsAre(expected));
  }

  INSTANTIATE_TEST_CASE_P(modulate, single_pair, Values(
    make_tuple("00", qpsk::symbol_t{in_phase: 1/sqrt2, quadrature: 1/sqrt2}),
    make_tuple("01", qpsk::symbol_t{in_phase: 1/sqrt2, quadrature: -1/sqrt2})
  ));
}
