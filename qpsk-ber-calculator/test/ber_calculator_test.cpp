#include <gmock/gmock.h>

#include "ber_calculator.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace {
  using qpsk::ber_calculator_t;
  using std::array;
  using std::make_tuple;
  using std::tuple;
  using std::vector;
  using testing::ElementsAre;
  using testing::ElementsAreArray;
  using testing::IsEmpty;
  using testing::Test;
  using testing::Values;
  using testing::WithParamInterface;

  struct bit_error_calculation : Test {
    ber_calculator_t calculator{};
  };

  TEST_F(bit_error_calculation, computes_no_rates_for_empty_input) {
    EXPECT_THAT(calculator.rates(array<int, 0>{}, array<int, 0>{}), IsEmpty());
  }

  TEST_F(bit_error_calculation, returns_a_single_zero_rate_for_two_identical_single_element_sequences) {
    EXPECT_THAT(calculator.rates(array{1}, array{1}), ElementsAre(0));
  }

  TEST_F(bit_error_calculation, returns_a_single_highest_rate_for_two_dissimilar_single_element_sequences) {
    EXPECT_THAT(calculator.rates(array{1}, array{2}), ElementsAre(1));
  }

  struct giving_numeric_sequences_and_expected_rate :
    public bit_error_calculation,
    public WithParamInterface<tuple<vector<int>, vector<int>, float>> {
  };

  TEST_P(giving_numeric_sequences_and_expected_rate, computes_correct_rate) {
    auto const [subject, sampling, rate] = GetParam();
    EXPECT_THAT(calculator.rates(subject, sampling), ElementsAre(rate));
  }

  INSTANTIATE_TEST_CASE_P(bit_error_calculation, giving_numeric_sequences_and_expected_rate,
    Values(
      make_tuple(vector{1, 2}, vector{1, 2}, 0),
      make_tuple(vector{1, 2, 3, 4}, vector{1, 2, 3, 0}, 1./4),
      make_tuple(vector{1, 2, 3, 4}, vector{1, 2, 0, 4}, 1./4),
      make_tuple(vector{1, 2, 3, 4}, vector{1, 0, 3, 4}, 1./4),
      make_tuple(vector{1, 2, 3, 4}, vector{0, 2, 3, 4}, 1./4),
      make_tuple(vector{1, 2, 3}, vector{1, 2, 0}, 1./3),
      make_tuple(vector{1, 2}, vector{1, 0}, 1./2),
      make_tuple(vector{1, 2}, vector{3, 4}, 1),
      make_tuple(vector{1}, vector{1, 2}, 1./2),
      make_tuple(vector{1, 2}, vector{1}, 0),
      make_tuple(vector{1, 2}, vector{2}, 1)
    )
  );

  struct giving_numeric_sequences_interval_and_expected_rates :
    public bit_error_calculation,
    public WithParamInterface<tuple<vector<int>, vector<int>, size_t, vector<float>>> {
  };

  TEST_P(giving_numeric_sequences_interval_and_expected_rates, computes_correct_rates) {
    auto const [subject, sampling, interval, rates] = GetParam();
    EXPECT_THAT(calculator.rates(subject, sampling, interval), ElementsAreArray(rates));
  }

  INSTANTIATE_TEST_CASE_P(bit_error_calculation, giving_numeric_sequences_interval_and_expected_rates,
    Values(
      make_tuple(vector{1, 2}, vector{1, 2}, 1, vector{0.0f, 0.0f}),
      make_tuple(vector{1, 2}, vector{2, 2}, 1, vector{1.0f, 0.0f}),
      make_tuple(vector{1, 2, 3, 4}, vector{1, 2, 3, 4}, 2, vector{0.0f, 0.0f}),
      make_tuple(vector{1, 2, 3, 4}, vector{1, 0, 0, 4}, 2, vector{1.f/2, 1.f/2}),
      make_tuple(vector{1}, vector{1, 2}, 1, vector{0.0f, 1.f}),
      make_tuple(vector{1, 2}, vector{1}, 1, vector{0.0f}),
      make_tuple(vector{1, 2, 3}, vector{1, 2, 3, 4}, 2, vector{0.0f, 1.f/2})
    )
  );
}
