#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Real;

class Acos : public IFunctionCRTP<INumber, Acos, INumber> {
public:
  Acos() = default;

  std::string toString() const override {
    return "acos";
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::Acos);
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;

private:
  static std::unique_ptr<IMathObject> multiAcosSimplify(const INumber &rhs);

  static std::unique_ptr<IMathObject> acosSimplify(const Real &rhs);
};

}
