#include <gtest/gtest.h>

#include "fintamath/core/IArithmetic.hpp"

#include "fintamath/exceptions/InvalidInputBinaryOperatorException.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

namespace {

class TestArithmetic : public IArithmeticCRTP<TestArithmetic> {
protected:
  TestArithmetic &add(const TestArithmetic & /* rhs */) override {
    return *this;
  }

  TestArithmetic &substract(const TestArithmetic & /* rhs */) override {
    return *this;
  }

  TestArithmetic &multiply(const TestArithmetic & /* rhs */) override {
    return *this;
  }

  TestArithmetic &divide(const TestArithmetic & /* rhs */) override {
    return *this;
  }

  TestArithmetic &negate() override {
    return *this;
  }
};

}

TEST(ArithmeticTests, addTest) {
  std::unique_ptr<IArithmetic> m1 = std::make_unique<Integer>(1);
  std::unique_ptr<IArithmetic> m2 = std::make_unique<Rational>(2);
  std::unique_ptr<IArithmetic> m3 = std::make_unique<Rational>(1, 2);

  EXPECT_EQ((*m1 + *m1)->toString(), "2");
  EXPECT_EQ((*m2 + *m2)->toString(), "4");
  EXPECT_EQ((*m1 + *m2)->toString(), "3");
  EXPECT_EQ((*m2 + *m1)->toString(), "3");

  EXPECT_EQ((*m1 + *m3)->toString(), "3/2");
  EXPECT_EQ((*m2 + *m3)->toString(), "5/2");
  EXPECT_EQ((*m3 + *m1)->toString(), "3/2");
  EXPECT_EQ((*m3 + *m2)->toString(), "5/2");
  EXPECT_EQ((*m3 + *m3)->toString(), "1");

  EXPECT_TRUE(is<Integer>(*m1 + *m1));
  EXPECT_TRUE(is<Integer>(*m2 + *m2));
  EXPECT_TRUE(is<Integer>(*m1 + *m2));
  EXPECT_TRUE(is<Integer>(*m2 + *m1));

  EXPECT_TRUE(is<Rational>(*m1 + *m3));
  EXPECT_TRUE(is<Rational>(*m2 + *m3));
  EXPECT_TRUE(is<Rational>(*m3 + *m1));
  EXPECT_TRUE(is<Rational>(*m3 + *m2));
  EXPECT_TRUE(is<Integer>(*m3 + *m3));

  EXPECT_THROW(*m1 + TestArithmetic(), InvalidInputBinaryOperatorException);
  EXPECT_THROW(TestArithmetic() + *m1, InvalidInputBinaryOperatorException);

  Integer a;
  EXPECT_EQ((a += 3).toString(), "3");
  EXPECT_EQ((Rational() + 1).toString(), "1");
  EXPECT_EQ((-1 + Rational()).toString(), "-1");
}

TEST(ArithmeticTests, subTest) {
  std::unique_ptr<IArithmetic> m1 = std::make_unique<Integer>(1);
  std::unique_ptr<IArithmetic> m2 = std::make_unique<Rational>(2);
  std::unique_ptr<IArithmetic> m3 = std::make_unique<Rational>(1, 2);

  EXPECT_EQ((*m1 - *m1)->toString(), "0");
  EXPECT_EQ((*m2 - *m2)->toString(), "0");
  EXPECT_EQ((*m1 - *m2)->toString(), "-1");
  EXPECT_EQ((*m2 - *m1)->toString(), "1");

  EXPECT_EQ((*m1 - *m3)->toString(), "1/2");
  EXPECT_EQ((*m2 - *m3)->toString(), "3/2");
  EXPECT_EQ((*m3 - *m1)->toString(), "-1/2");
  EXPECT_EQ((*m3 - *m2)->toString(), "-3/2");
  EXPECT_EQ((*m3 - *m3)->toString(), "0");

  EXPECT_TRUE(is<Integer>(*m1 - *m1));
  EXPECT_TRUE(is<Integer>(*m2 - *m2));
  EXPECT_TRUE(is<Integer>(*m1 - *m2));
  EXPECT_TRUE(is<Integer>(*m2 - *m1));

  EXPECT_TRUE(is<Rational>(*m1 - *m3));
  EXPECT_TRUE(is<Rational>(*m2 - *m3));
  EXPECT_TRUE(is<Rational>(*m3 - *m1));
  EXPECT_TRUE(is<Rational>(*m3 - *m2));
  EXPECT_TRUE(is<Integer>(*m3 - *m3));

  EXPECT_THROW(*m1 - TestArithmetic(), InvalidInputBinaryOperatorException);
  EXPECT_THROW(TestArithmetic() - *m1, InvalidInputBinaryOperatorException);

  Integer a;
  EXPECT_EQ((a -= 3).toString(), "-3");
  EXPECT_EQ((Integer() - 1).toString(), "-1");
  EXPECT_EQ((-1 - Integer()).toString(), "-1");
}

TEST(ArithmeticTests, mulTest) {
  std::unique_ptr<IArithmetic> m1 = std::make_unique<Integer>(1);
  std::unique_ptr<IArithmetic> m2 = std::make_unique<Rational>(2);
  std::unique_ptr<IArithmetic> m3 = std::make_unique<Rational>(1, 2);

  EXPECT_EQ((*m1 * *m1)->toString(), "1");
  EXPECT_EQ((*m2 * *m2)->toString(), "4");
  EXPECT_EQ((*m1 * *m2)->toString(), "2");
  EXPECT_EQ((*m2 * *m1)->toString(), "2");

  EXPECT_EQ((*m1 * *m3)->toString(), "1/2");
  EXPECT_EQ((*m2 * *m3)->toString(), "1");
  EXPECT_EQ((*m3 * *m1)->toString(), "1/2");
  EXPECT_EQ((*m3 * *m2)->toString(), "1");
  EXPECT_EQ((*m3 * *m3)->toString(), "1/4");

  EXPECT_TRUE(is<Integer>(*m1 * *m1));
  EXPECT_TRUE(is<Integer>(*m2 * *m2));
  EXPECT_TRUE(is<Integer>(*m1 * *m2));
  EXPECT_TRUE(is<Integer>(*m2 * *m1));

  EXPECT_TRUE(is<Rational>(*m1 * *m3));
  EXPECT_TRUE(is<Integer>(*m2 * *m3));
  EXPECT_TRUE(is<Rational>(*m3 * *m1));
  EXPECT_TRUE(is<Integer>(*m3 * *m2));
  EXPECT_TRUE(is<Rational>(*m3 * *m3));

  EXPECT_THROW(*m1 * TestArithmetic(), InvalidInputBinaryOperatorException);
  EXPECT_THROW(TestArithmetic() * *m1, InvalidInputBinaryOperatorException);

  Integer a = 2;
  EXPECT_EQ((a *= 3).toString(), "6");
  EXPECT_EQ((Integer(2) * 2).toString(), "4");
  EXPECT_EQ((-2 * Integer(2)).toString(), "-4");
}

TEST(ArithmeticTests, divTest) {
  std::unique_ptr<IArithmetic> m1 = std::make_unique<Integer>(1);
  std::unique_ptr<IArithmetic> m2 = std::make_unique<Rational>(2);
  std::unique_ptr<IArithmetic> m3 = std::make_unique<Rational>(1, 2);

  EXPECT_EQ((*m1 / *m1)->toString(), "1");
  EXPECT_EQ((*m2 / *m2)->toString(), "1");
  EXPECT_EQ((*m1 / *m2)->toString(), "1/2");
  EXPECT_EQ((*m2 / *m1)->toString(), "2");

  EXPECT_EQ((*m1 / *m3)->toString(), "2");
  EXPECT_EQ((*m2 / *m3)->toString(), "4");
  EXPECT_EQ((*m3 / *m1)->toString(), "1/2");
  EXPECT_EQ((*m3 / *m2)->toString(), "1/4");
  EXPECT_EQ((*m3 / *m3)->toString(), "1");

  EXPECT_TRUE(is<Integer>(*m1 / *m1));
  EXPECT_TRUE(is<Integer>(*m2 / *m2));
  EXPECT_TRUE(is<Rational>(*m1 / *m2));
  EXPECT_TRUE(is<Integer>(*m2 / *m1));

  EXPECT_TRUE(is<Integer>(*m1 / *m3));
  EXPECT_TRUE(is<Integer>(*m2 / *m3));
  EXPECT_TRUE(is<Rational>(*m3 / *m1));
  EXPECT_TRUE(is<Rational>(*m3 / *m2));
  EXPECT_TRUE(is<Integer>(*m3 / *m3));

  EXPECT_THROW(*m1 / TestArithmetic(), InvalidInputBinaryOperatorException);
  EXPECT_THROW(TestArithmetic() / *m1, InvalidInputBinaryOperatorException);

  Integer a = 4;
  EXPECT_EQ((a /= 2).toString(), "2");
  EXPECT_EQ((Integer(4) / 2).toString(), "2");
  EXPECT_EQ((-2 / Integer(2)).toString(), "-1");
}

TEST(ArithmeticTests, unaryPlusTest) {
  std::unique_ptr<IArithmetic> m1 = std::make_unique<Integer>(1);
  EXPECT_EQ((+*m1)->toString(), "1");

  EXPECT_EQ((+Integer(1)).toString(), "1");
}

TEST(ArithmeticTests, negateTest) {
  std::unique_ptr<IArithmetic> m1 = std::make_unique<Integer>(1);
  EXPECT_EQ((-*m1)->toString(), "-1");

  EXPECT_EQ((-Integer(1)).toString(), "-1");
}

TEST(ArithmeticTests, multimethodsTest) {
  IArithmetic::addMultiAddFunction<TestArithmetic, Integer>([](const TestArithmetic &lhs, const Integer &rhs) {
    return cast<IArithmetic>(ZERO.clone());
  });
  EXPECT_EQ((TestArithmetic() + Integer(1))->toString(), ZERO.toString());

  IArithmetic::addMultiSubFunction<TestArithmetic, Integer>([](const TestArithmetic &lhs, const Integer &rhs) {
    return cast<IArithmetic>(ZERO.clone());
  });
  EXPECT_EQ((TestArithmetic() - Integer(1))->toString(), ZERO.toString());

  IArithmetic::addMultiMulFunction<TestArithmetic, Integer>([](const TestArithmetic &lhs, const Integer &rhs) {
    return cast<IArithmetic>(ZERO.clone());
  });
  EXPECT_EQ((TestArithmetic() * Integer(1))->toString(), ZERO.toString());

  IArithmetic::addMultiDivFunction<TestArithmetic, Integer>([](const TestArithmetic &lhs, const Integer &rhs) {
    return cast<IArithmetic>(ZERO.clone());
  });
  EXPECT_EQ((TestArithmetic() / Integer(1))->toString(), ZERO.toString());
}
