#include "fintamath/functions/trigonometry/Asin.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Asin::toString() const {
    return "asin";
  }

  MathObjectPtr Asin::operator()(const MathObject &rhs) const {
    constexpr int64_t defaultPrecision = 45;
    if (!rhs.instanceOf<Number>()) {
      throw std::invalid_argument("Rhs must be Number");
    }

    auto newRhs = meta::convertMathObject(rhs, Rational());
    return asin(newRhs->to<Rational>(), defaultPrecision).simplify();
  }

  MathObjectPtr Asin::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 1) {
      throw std::invalid_argument("The number of arguments must be 1");
    }
    return Asin::operator()(argsVect.at(0).get());
  }
}