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

  struct reader_test : public Test {
    reader_t reader;
    vector<symbol_t> symbols;
  };

  struct reader_read_produces_no_symbols : public reader_test,
    public WithParamInterface<string_view> {
  };

  TEST_P(reader_read_produces_no_symbols, test) {
    auto const input = GetParam();
    reader.read(begin(input), end(input), back_inserter(symbols));
    EXPECT_THAT(symbols, IsEmpty());
  }

  INSTANTIATE_TEST_CASE_P(for_empty_input, reader_read_produces_no_symbols,
    Values("", " ", "\n", "\t", " \n ", " \t ")
  );

  struct reader_read_produces_single_symbol : public reader_test,
    public WithParamInterface<tuple<string_view, symbol_t>> {
  };

  TEST_P(reader_read_produces_single_symbol, test) {
    auto const [input, expected] = GetParam();
    reader.read(begin(input), end(input), back_inserter(symbols));
    EXPECT_THAT(symbols, ElementsAre(expected));
  }

  INSTANTIATE_TEST_CASE_P(for_a_pair_of_comma_delimited_numbers, reader_read_produces_single_symbol,
    Values(
      make_tuple("0.1,0.2"sv, symbol_t{in_phase: 0.1, quadrature: 0.2}),
      make_tuple("-0.1,0.2"sv, symbol_t{in_phase: -0.1, quadrature: 0.2}),
      make_tuple("0.1,-0.2"sv, symbol_t{in_phase: 0.1, quadrature: -0.2}),
      make_tuple("-0.1,-0.2"sv, symbol_t{in_phase: -0.1, quadrature: -0.2})
    )
  );

  INSTANTIATE_TEST_CASE_P(for_a_single_number, reader_read_produces_no_symbols,
    Values("0", "0.1", "0.1," , ",0.1")
  );

  struct reader_read_produces_symbols : public reader_test,
    public WithParamInterface<tuple<string_view, vector<symbol_t>>> {
  };

  TEST_P(reader_read_produces_symbols, test) {
    auto const [input, expected] = GetParam();
    reader.read(begin(input), end(input), back_inserter(symbols));
    EXPECT_THAT(symbols, ElementsAreArray(expected));
  }

  INSTANTIATE_TEST_CASE_P(for_a_sequence_of_whitespace_separated_blocks_of_comma_delimeted_numbers,
    reader_read_produces_symbols,
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
    reader_read_produces_single_symbol,
    Values(
      make_tuple("I0.1,Q0.2"sv, symbol_t{in_phase: 0.1, quadrature: 0.2}),
      make_tuple("I-0.1,Q-0.2"sv, symbol_t{in_phase: -0.1, quadrature: -0.2}),
      make_tuple("I+0.1,Q+0.2"sv, symbol_t{in_phase: 0.1, quadrature: 0.2})
    )
  );

  INSTANTIATE_TEST_CASE_P(for_a_sequence_of_whitespace_separated_blocks_of_comma_delimeted_numbers_in_parenthesis,
    reader_read_produces_symbols,
    Values(
      make_tuple("(0.1,0.2) (0.3,0.4)"sv, vector{
        symbol_t{in_phase: 0.1, quadrature: 0.2}, symbol_t{in_phase: 0.3, quadrature: 0.4},
      })
    )
  );
}
