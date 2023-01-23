#pragma once

#include <memory>
#include <vector>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/parser/Parser.hpp"
#include "fintamath/parser/Tokenizer.hpp"

namespace fintamath {

class IFunction;

using ArgumentsVector = std::vector<std::reference_wrapper<const class IMathObject>>;

class IExpression;
using ExpressionPtr = std::unique_ptr<IExpression>;

class IExpression : virtual public IMathObject {
public:
  ~IExpression() override = default;

  virtual uint16_t getBaseOperatorPriority() const = 0;

  virtual void setPrecision(uint8_t precision) = 0;

  MathObjectPtr simplify() const override;

  virtual MathObjectPtr simplify(bool isPrecise) const = 0;

  virtual std::vector<MathObjectPtr> getVariables() const;

protected:
  static bool skipBrackets(const TokenVector &tokens, size_t &openBracketIndex);

  static TokenVector cutBraces(const TokenVector &tokens);

  static std::string tryPutInBracketsIfNeg(const MathObjectPtr &obj);

  void validateFunctionArgs(const IFunction &func, const ArgumentsVector &args) const;

  template <typename T>
  static void pushPolynomToPolynom(typename T::Polynom &push, typename T::Polynom &cont);
};

template <typename T>
void IExpression::pushPolynomToPolynom(typename T::Polynom &push, typename T::Polynom &cont) {
  for (const auto &elem : push) {
    cont.emplace_back(elem);
  }
}

template <typename Derived>
class IExpressionCRTP : virtual public IExpression, virtual public IMathObjectCRTP<Derived> {};

}
