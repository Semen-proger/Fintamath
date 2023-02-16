#include "fintamath/functions/hyperbolic/Cosh.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr Cosh::call(const ArgumentsVector &argsVect) const {
  return cosh(convert<Real>(argsVect.front())).toMinimalObject();
}

}
