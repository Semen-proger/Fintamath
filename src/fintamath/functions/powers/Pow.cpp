#include "fintamath/functions/powers/Pow.hpp"

#include "fintamath/functions/powers/Root.hpp"
#include "fintamath/functions/powers/Sqrt.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/Undefined.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Pow::call(const ArgumentsRefVector &argsVect) const {
  const auto &lhs = cast<INumber>(argsVect.front().get());
  const auto &rhs = cast<INumber>(argsVect.back().get());

  if (lhs == Integer(0) && rhs == Integer(0)) {
    return Undefined().clone();
  }

  if (rhs < Integer(0)) {
    if (lhs == Integer(0)) {
      return ComplexInf().clone();
    }

    return multiPowSimplify(*(Rational(1) / lhs), *(-rhs));
  }

  return multiPowSimplify(lhs, rhs);
}

std::unique_ptr<IMathObject> Pow::multiPowSimplify(const INumber &lhs, const INumber &rhs) {
  static const auto multiPow = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &, const INumber &)> outMultiPow;

    outMultiPow.add<Integer, Integer>([](const Integer &inLhs, const Integer &inRhs) {
      return powSimplify(inLhs, inRhs);
    });

    outMultiPow.add<Rational, Rational>([](const Rational &inLhs, const Rational &inRhs) {
      return powSimplify(inLhs, inRhs);
    });

    outMultiPow.add<Real, Real>([](const Real &inLhs, const Real &inRhs) {
      return powSimplify(inLhs, inRhs);
    });

    return outMultiPow;
  }();

  if (auto rhsConv = convert(lhs, rhs)) {
    return multiPow(lhs, *rhsConv);
  }

  auto lhsConv = convert(rhs, lhs);
  return multiPow(*lhsConv, rhs);
}

std::unique_ptr<IMathObject> Pow::powSimplify(const Integer &lhs, const Integer &rhs) {
  return pow(lhs, rhs).toMinimalObject();
}

std::unique_ptr<IMathObject> Pow::powSimplify(const Rational &lhs, const Rational &rhs) {
  const Integer &lhsNumerator = lhs.numerator();
  const Integer &lhsDenominator = lhs.denominator();

  const Integer &rhsNumerator = rhs.numerator();
  const Integer &rhsDenominator = rhs.denominator();

  if (rhsDenominator == 1) {
    if (lhsDenominator == 1) {
      return pow(lhsNumerator, rhsNumerator).toMinimalObject();
    }

    return pow(lhs, rhsNumerator).toMinimalObject();
  }

  if (lhs < Integer(0)) {
    // TODO: complex numbers
    return {};
  }

  if (lhsDenominator == 1) {
    return Root()(*multiPowSimplify(lhsNumerator, rhsNumerator), rhsDenominator);
  }

  return Root()(*multiPowSimplify(lhs, rhsNumerator), rhsDenominator);
}

std::unique_ptr<IMathObject> Pow::powSimplify(const Real &lhs, const Real &rhs) {
  try {
    return pow(lhs, rhs).toMinimalObject();
  }
  catch (const UndefinedException &) {
    return {};
  }
}

}
