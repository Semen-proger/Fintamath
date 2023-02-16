#include "fintamath/functions/trigonometry/Cot.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr Cot::call(const ArgumentsVector &argsVect) const {
  return cot(convert<Real>(argsVect.front())).toMinimalObject();
}

}
