#include <gmock/gmock.h>

#include "qpsk/snr.hpp"

#include <tuple>

namespace {
  using namespace qpsk::literals;
  using qpsk::snr_t;
  using std::make_tuple;
  using std::tuple;
  using testing::Eq;
  using testing::Test;
  using testing::Values;
  using testing::WithParamInterface;

  struct giving_snr_and_linear_factor : public Test,
    public WithParamInterface<tuple<snr_t, float>> {
  };

  TEST_P(giving_snr_and_linear_factor, calculates_correct_linear_factor) {
    auto const [snr, expected_linar] = GetParam();
    EXPECT_THAT(snr.linear(), Eq(expected_linar));
  }

  INSTANTIATE_TEST_CASE_P(for_snr_id_dB, giving_snr_and_linear_factor, Values(
    make_tuple(0_dB, 1),
    make_tuple(10_dB, 10),
    make_tuple(20_dB, 100),
    make_tuple(30_dB, 1'000),
    make_tuple(40_dB, 10'000),
    make_tuple(50_dB, 100'000),
    make_tuple(100_dB, 10'000'000'000)
  ));
}
