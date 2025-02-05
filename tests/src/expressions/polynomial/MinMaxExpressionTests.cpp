#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/calculus/Min.hpp"

using namespace fintamath;

TEST(MinMaxExpressionTests, getTypeIdTest) {
  EXPECT_EQ(makeExpr(Min(), Integer(0), Integer(0))->getTypeId(), MathObjectTypeId(MathObjectType::MinMaxExpression));
}
