#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class More : public IOperatorCRTP<Boolean, More, IComparable, IComparable> {
public:
  More() : IOperatorCRTP(IOperator::Priority::Comparison) {
  }

  std::string toString() const override {
    return ">";
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::More);
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
