#include <gmock/gmock.h>
#include <iterator>
#include <vector>

#include "modulator.hpp"

namespace {
  using std::back_inserter;
  using std::begin;
  using std::end;
  using std::vector;
  using testing::IsEmpty;

  TEST(modulate, produces_empty_output_when_input_is_empty) {
    vector<char> input{};
    vector<qpsk::symbol_t> symbols{};
    qpsk::modulate(begin(input), end(input), back_inserter(symbols));
    EXPECT_THAT(symbols, IsEmpty());
  }
}
