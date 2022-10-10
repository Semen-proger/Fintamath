#include "fintamath/functions/arithmetic/Add.hpp"

#include "fintamath/core/Arithmetic.hpp"

namespace fintamath {
  int Add::getPriority() const {
    return priority;
  }

  std::string Add::toString() const {
    return "+";
  }

  MathObjectPtr Add::operator()(const MathObject &lhs, const MathObject &rhs) const {
    if (!lhs.instanceOf<Arithmetic>() || !rhs.instanceOf<Arithmetic>()) {
      throw std::invalid_argument("Lhs and Rhs must be Arithmetic");
    }
    return lhs.to<Arithmetic>() + rhs.to<Arithmetic>();
  }

  MathObjectPtr Add::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 2) {
      throw std::invalid_argument("The number of arguments must be 2");
    }
    return Add::operator()(argsVect.at(0).get(), argsVect.at(1).get());
  }
}