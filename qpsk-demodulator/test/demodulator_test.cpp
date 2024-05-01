#include <gmock/gmock.h>

#include "demodulator.hpp"

namespace {
  using testing::Eq;

  TEST(demodulator, dummy) {
    EXPECT_THAT(0, Eq(1));
  }
}
