#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/literals/constants/Undefined.hpp"

namespace fintamath {

std::string IBinaryExpression::toString() const {
  if (auto oper = cast<IOperator>(func)) {
    return binaryOperatorToString(*oper, lhsChild, rhsChild);
  }

  return functionToString(*func, {lhsChild, rhsChild});
}

std::shared_ptr<IFunction> IBinaryExpression::getFunction() const {
  return func;
}

ArgumentsPtrVector IBinaryExpression::getChildren() const {
  return {lhsChild, rhsChild};
}

ArgumentPtr IBinaryExpression::preSimplify() const {
  auto simpl = cast<IBinaryExpression>(clone());
  preSimplifyChild(simpl->lhsChild);
  preSimplifyChild(simpl->rhsChild);

  if (is<Undefined>(simpl->lhsChild) || is<Undefined>(simpl->rhsChild)) {
    return Undefined().clone();
  }

  ArgumentPtr res = simpl->useSimplifyFunctions(getFunctionsForPreSimplify());

  if (res && *res != *simpl) {
    preSimplifyChild(res);
    return res;
  }

  return simpl;
}

ArgumentPtr IBinaryExpression::postSimplify() const {
  auto simpl = cast<IBinaryExpression>(clone());
  postSimplifyChild(simpl->lhsChild);
  postSimplifyChild(simpl->rhsChild);

  if (is<Undefined>(simpl->lhsChild) || is<Undefined>(simpl->rhsChild)) {
    return Undefined().clone();
  }

  if (ArgumentPtr res = callFunction(*simpl->func, {simpl->lhsChild, simpl->rhsChild})) {
    return res;
  }

  ArgumentPtr res = simpl->useSimplifyFunctions(getFunctionsForPostSimplify());

  if (res && *res != *simpl) {
    postSimplifyChild(res);
    return res;
  }

  return simpl;
}

ArgumentPtr IBinaryExpression::preciseSimplify() const {
  auto preciseExpr = cast<IBinaryExpression>(clone());
  preciseSimplifyChild(preciseExpr->lhsChild);
  preciseSimplifyChild(preciseExpr->rhsChild);
  return preciseExpr;
}

ArgumentPtr IBinaryExpression::simplify() const {
  ArgumentPtr simpl = cast<IBinaryExpression>(clone());
  preSimplifyChild(simpl);
  postSimplifyChild(simpl);
  return simpl;
}

ArgumentPtr IBinaryExpression::useSimplifyFunctions(const SimplifyFunctionsVector &simplFuncs) const {
  for (const auto &simplFunc : simplFuncs) {
    if (auto res = simplFunc(*func, lhsChild, rhsChild)) {
      return res;
    }
  }

  return {};
}

IBinaryExpression::SimplifyFunctionsVector IBinaryExpression::getFunctionsForPreSimplify() const {
  return {};
}

IBinaryExpression::SimplifyFunctionsVector IBinaryExpression::getFunctionsForPostSimplify() const {
  return {};
}

void IBinaryExpression::setChildren(const ArgumentsPtrVector &childVect) {
  if (childVect.size() != 2) {
    throw InvalidInputFunctionException(toString(), argumentVectorToStringVector(childVect));
  }

  lhsChild = childVect[0];
  rhsChild = childVect[1];
}

}
