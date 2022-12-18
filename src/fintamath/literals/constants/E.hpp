#pragma once

#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {
  class E : public IConstantCRTP<E> {
  public:
    std::string toString() const override;

    std::string getClassName() const override;

  protected:
    Expression getValue() const override;
  };
}