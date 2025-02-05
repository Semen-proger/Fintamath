#pragma once

#include <memory>

#include "fintamath/literals/ILiteral.hpp"

namespace fintamath {

class IConstant : public ILiteral {
public:
  virtual size_t getReturnTypeId() const = 0;

  std::unique_ptr<IMathObject> operator()() const {
    return call();
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<IConstant, T>>>
  static void registerType() {
    Parser::registerType<T>(getParser());
  }

  static std::unique_ptr<IConstant> parse(const std::string &parsedStr) {
    return Parser::parse<std::unique_ptr<IConstant>>(getParser(), parsedStr);
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::IConstant);
  }

protected:
  virtual std::unique_ptr<IMathObject> call() const = 0;

private:
  static Parser::Map<std::unique_ptr<IConstant>> &getParser();
};

template <typename Return, typename Derived>
class IConstantCRTP : public IConstant {
#define FINTAMATH_I_CONSTANT_CRTP IConstantCRTP<Return, Derived>
#include "fintamath/literals/constants/IConstantCRTP.hpp"
#undef FINTAMATH_I_CONSTANT_CRTP
};

}
