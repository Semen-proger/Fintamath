#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class INumber;

class Inv : public IFunctionCRTP<INumber, Inv, INumber> {
public:
  Inv() = default;

  std::string toString() const override {
    return "inv";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};
}