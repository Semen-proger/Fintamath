#include <gtest/gtest.h>

#include "fintamath/core/Converter.hpp"

#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

TEST(ConverterTests, convertTest) {
  EXPECT_TRUE(is<Integer>(convert(Integer(), Integer())));

  EXPECT_TRUE(is<Rational>(convert(Rational(), Rational())));
  EXPECT_TRUE(is<Rational>(convert(Rational(), Integer())));
  EXPECT_FALSE(convert(Integer(), Rational()));

  EXPECT_TRUE(is<Real>(convert(Real(), Real())));
  EXPECT_TRUE(is<Real>(convert(Real(), Integer())));
  EXPECT_FALSE(convert(Integer(), Real()));
  EXPECT_TRUE(is<Real>(convert(Real(), Rational())));
  EXPECT_FALSE(convert(Rational(), Real()));
}

TEST(ConverterTests, convertTemplateTest) {
  EXPECT_TRUE(is<Integer>(convert<Integer>(Integer())));

  EXPECT_TRUE(is<Rational>(convert<Rational>(Rational())));
  EXPECT_TRUE(is<Rational>(convert<Rational>(Integer())));
  EXPECT_FALSE(convert<Integer>(Rational()));

  EXPECT_TRUE(is<Real>(convert<Real>(Real())));
  EXPECT_TRUE(is<Real>(convert<Real>(Integer())));
  EXPECT_FALSE(convert<Integer>(Real()));
  EXPECT_TRUE(is<Real>(convert<Real>(Rational())));
  EXPECT_FALSE(convert<Rational>(Real()));
}
