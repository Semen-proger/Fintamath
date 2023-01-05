#pragma once

#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class IArithmetic;

class Sub : public IOperatorCRTP<Sub, IArithmetic, IArithmetic> {
public:
  Sub() : IOperatorCRTP(IOperator::Priority::Addition) {
  }

  std::string toString() const override {
    return "-";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
