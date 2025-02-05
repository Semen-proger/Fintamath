#include "fintamath/functions/arithmetic/Frac.hpp"

#include "fintamath/functions/arithmetic/Div.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Frac::call(const ArgumentsRefVector &argsVect) const {
  return Div()(argsVect);
}

}
