#include <gtest/gtest.h>

#include "audioEffects.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
  audioEffects a;
  EXPECT_EQ(a.returnFour(), 4);
  
}
