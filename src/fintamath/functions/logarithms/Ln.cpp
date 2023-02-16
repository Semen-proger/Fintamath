#include "fintamath/functions/logarithms/Ln.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr Ln::call(const ArgumentsVector &argsVect) const {
  return ln(convert<Real>(argsVect.front())).toMinimalObject();
}

}
