#include <gmock/gmock.h>

#include <iterator>
#include <string_view>
#include <tuple>
#include <vector>

#include "qpsk/reader.hpp"

namespace {
  using namespace std::literals;
  using qpsk::reader_t;
  using qpsk::symbol_t;
  using std::string_view;
  using std::tuple;
  using std::vector;
  using testing::ElementsAre;
  using testing::ElementsAreArray;
  using testing::IsEmpty;
  using testing::Test;
  using testing::Values;
  using testing::WithParamInterface;

  struct reading_test : public Test {
    reader_t reader;
    vector<symbol_t> symbols;
  };

  struct reading_text_sequence : public reading_test,
    public WithParamInterface<string_view> {
  };

  TEST_P(reading_text_sequence, returns_no_symbols) {
    auto const input = GetParam();
    reader.read(begin(input), end(input), back_inserter(symbols));
    EXPECT_THAT(symbols, IsEmpty());
  }

  INSTANTIATE_TEST_CASE_P(for_empty_input, reading_text_sequence,
    Values("", " ", "\n", "\t", " \n ", " \t ")
  );

  struct reading_text_sequence_expecting_single_symbol : public reading_test,
    public WithParamInterface<tuple<string_view, symbol_t>> {
  };

  TEST_P(reading_text_sequence_expecting_single_symbol, returns_correct_symbol) {
    auto const [input, expected] = GetParam();
    reader.read(begin(input), end(input), back_inserter(symbols));
    EXPECT_THAT(symbols, ElementsAre(expected));
  }

  INSTANTIATE_TEST_CASE_P(for_a_pair_of_comma_delimited_numbers,
    reading_text_sequence_expecting_single_symbol,
    Values(
      make_tuple("0.1,0.2"sv, symbol_t{in_phase: 0.1, quadrature: 0.2}),
      make_tuple("-0.1,0.2"sv, symbol_t{in_phase: -0.1, quadrature: 0.2}),
      make_tuple("0.1,-0.2"sv, symbol_t{in_phase: 0.1, quadrature: -0.2}),
      make_tuple("-0.1,-0.2"sv, symbol_t{in_phase: -0.1, quadrature: -0.2})
    )
  );

  INSTANTIATE_TEST_CASE_P(for_a_single_number, reading_text_sequence,
    Values("0", "0.1", "0.1," , ",0.1")
  );

  struct reading_text_sequence_expecting_symbols : public reading_test,
    public WithParamInterface<tuple<string_view, vector<symbol_t>>> {
  };

  TEST_P(reading_text_sequence_expecting_symbols, returns_expected_symbols) {
    auto const [input, expected] = GetParam();
    reader.read(begin(input), end(input), back_inserter(symbols));
    EXPECT_THAT(symbols, ElementsAreArray(expected));
  }

  INSTANTIATE_TEST_CASE_P(for_a_sequence_of_whitespace_separated_blocks_of_comma_delimeted_numbers,
    reading_text_sequence_expecting_symbols,
    Values(
      make_tuple("0.1,0.2 -0.3,-0.4", vector{
        symbol_t{in_phase: 0.1, quadrature: 0.2}, symbol_t{in_phase: -0.3, quadrature: -0.4}
      }),
      make_tuple("0.1,0.2\t0.3,0.4", vector{
        symbol_t{in_phase: 0.1, quadrature: 0.2}, symbol_t{in_phase: 0.3, quadrature: 0.4}
      }),
      make_tuple("0.1,0.2 \t \t\t  \t\t\t   0.3,0.4", vector{
        symbol_t{in_phase: 0.1, quadrature: 0.2}, symbol_t{in_phase: 0.3, quadrature: 0.4}
      })
    )
  );

  INSTANTIATE_TEST_CASE_P(for_a_pair_of_comma_delimited_numbers_with_prefixes,
    reading_text_sequence_expecting_single_symbol,
    Values(
      make_tuple("I0.1,Q0.2"sv, symbol_t{in_phase: 0.1, quadrature: 0.2}),
      make_tuple("I-0.1,Q-0.2"sv, symbol_t{in_phase: -0.1, quadrature: -0.2}),
      make_tuple("I+0.1,Q+0.2"sv, symbol_t{in_phase: 0.1, quadrature: 0.2})
    )
  );

  INSTANTIATE_TEST_CASE_P(
    for_a_sequence_of_whitespace_separated_blocks_of_comma_delimeted_numbers_in_parenthesis,
    reading_text_sequence_expecting_symbols,
    Values(
      make_tuple("(0.1,0.2) (0.3,0.4)"sv, vector{
        symbol_t{in_phase: 0.1, quadrature: 0.2}, symbol_t{in_phase: 0.3, quadrature: 0.4},
      })
    )
  );
}
