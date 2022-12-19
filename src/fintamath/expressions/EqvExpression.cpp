#include "fintamath/expressions/EqvExpression.hpp"
#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/comparison/Eqv.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/helpers/Converter.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/functions/Functions.hpp"
#include <cstdint>


namespace fintamath {
  EqvExpression::EqvExpression(const TokenVector &tokens) {
    parse(tokens);
  }

  EqvExpression::EqvExpression(const IMathObject &oper, const IMathObject &lhs, const IMathObject &rhs) {
    if(!oper.instanceOf<IOperator>() || oper.to<IOperator>().getOperatorPriority() != IOperator::Priority::Comparison){
      throw UndefinedBinaryOpearatorException(oper.toString(), lhs.toString(), rhs.toString());
    }
    if(lhs.is<EqvExpression>() || rhs.is<EqvExpression>()) {
      throw UndefinedBinaryOpearatorException(oper.toString(), lhs.toString(), rhs.toString());
    }

    this->oper = oper.clone();
    leftExpr = lhs.clone();
    rightExpr = rhs.clone();
  }

  EqvExpression::EqvExpression(const EqvExpression &rhs) noexcept {
    leftExpr = rhs.leftExpr->clone();
    rightExpr = rhs.rightExpr->clone();
    oper = rhs.oper->clone();
  }

  EqvExpression::EqvExpression(EqvExpression &&rhs) noexcept {
    leftExpr = rhs.leftExpr->clone();
    rightExpr = rhs.rightExpr->clone();
    oper = rhs.oper->clone();
  }

  EqvExpression &EqvExpression::operator=(const EqvExpression &rhs) noexcept {
    if (&rhs != this) {
      leftExpr = rhs.leftExpr->clone();
      rightExpr = rhs.rightExpr->clone();
      oper = rhs.oper->clone();
    }
    return *this;
  }

  EqvExpression &EqvExpression::operator=(EqvExpression &&rhs) noexcept {
    if (&rhs != this) {
      std::swap(leftExpr, rhs.leftExpr);
      std::swap(rightExpr, rhs.rightExpr);
      std::swap(oper, rhs.oper);
    }
    return *this;
  }

  std::string EqvExpression::toString() const {
    return leftExpr->toString() + oper->toString() + rightExpr->toString();
  }

  std::string EqvExpression::getClassName() const {
    return "EqvExpression";
  }

  MathObjectPtr EqvExpression::simplify() const {
    return simplify(true);
  }

  MathObjectPtr EqvExpression::simplify(bool isPrecise) const{
    auto cloneExpr = *this;
    AddExpression addExpr;
    addExpr.addElement(AddExpression::Element(cloneExpr.leftExpr->clone()));
    addExpr.addElement(AddExpression::Element(cloneExpr.rightExpr->clone(), true));
    cloneExpr.leftExpr = addExpr.simplify(isPrecise);
    cloneExpr.rightExpr = Integer(0).clone();

    if(cloneExpr.leftExpr->instanceOf<IComparable>()){
      auto b = oper->to<IOperator>()(*cloneExpr.leftExpr, *cloneExpr.rightExpr);
      return b.simplify(isPrecise);
    }
    return cloneExpr.clone();
  }

  uint16_t EqvExpression::getInfoPriority() {
    return (uint16_t)IOperator::Priority::Comparison;
  }

  void EqvExpression::parse(const TokenVector &tokens) {
    bool eqvOpers = false;
    for (size_t i = 0; i < tokens.size(); i++) {
      if (tokens[i] == "<" || tokens[i] == "<=" || tokens[i] == "=" || tokens[i] == ">=" || tokens[i] == ">") {
        if (eqvOpers) {
          throw InvalidInputException(*this, " number of comparison operators exceeded");
        }
        eqvOpers = true;
      }
    }

    for (size_t i = 0; i < tokens.size(); i++) {
      if (tokens[i] == "(" && !skipBrackets(tokens, i)) {
        throw InvalidInputException(*this, " braces must be closed");
      }
      if (i == tokens.size()) {
        break;
      }
      if (tokens[i] != "<" && tokens[i] != "<=" && tokens[i] != "=" && tokens[i] != ">=" && tokens[i] != ">") {
        continue;
      }
      if (i == tokens.size() - 1) {
        throw InvalidInputException(*this, " unexpected sign");
      }

      leftExpr = IExpression::parse(TokenVector(tokens.begin(), tokens.begin() + (long)i));
      rightExpr = IExpression::parse(TokenVector(tokens.begin() + (long)i + 1, tokens.end()));
      oper = IOperator::parse(tokens[i]);
      return;
    }
    throw InvalidInputException(*this, " not an EqvExpression");
  }

  void EqvExpression::setPrecision(uint8_t precision) {
    if(leftExpr->instanceOf<IExpression>()){
      auto copyExpr = helpers::cast<IExpression>(leftExpr);
      copyExpr->setPrecision(precision);
      leftExpr = copyExpr->clone();
    }
  }

  std::string EqvExpression::solve() const{
    Variable x("x");
    auto expr = simplify(false);
    if(!expr->is<EqvExpression>()){
      return expr->toString();
    }
    auto copyExpr = expr->to<EqvExpression>();
    if(!copyExpr.oper->is<Eqv>()){
      return expr->toString();
    }
    if(!copyExpr.detectOneVariable(x)){
      return toString();
    }

    auto results = copyExpr.solvePowEquation(x);
    if(results.empty()){
      return toString();
    }
    std::string resultStr = x.toString() + " in {";
    for(const auto& res : results){
      resultStr += res->toString();
      resultStr += ",";
    }
    resultStr.pop_back();
    resultStr += "}";
    return resultStr;
  }

  std::string EqvExpression::solve(uint8_t precision) const{
    Variable x("x");
    if(!detectOneVariable(x)){
      auto copyExpr = *this;
      copyExpr.setPrecision(precision);
      return copyExpr.toString();
    }

    auto results = solvePowEquation(x);
    if(results.empty()){
      auto copyExpr = *this;
      copyExpr.setPrecision(precision);
      return copyExpr.toString();
    }
    std::string resultStr = x.toString() + " in {";
    for(const auto& res : results){
      resultStr += Expression(*res).toString(precision);
      resultStr += ",";
    }
    resultStr.pop_back();
    resultStr += "}";
    return resultStr;
  }

  std::vector<MathObjectPtr> EqvExpression::solvePowEquation(const Variable& x) const {
    auto results = solveQuadraticEquation(x.clone());
    return results;
  }

  std::vector<MathObjectPtr> EqvExpression::solveQuadraticEquation(const MathObjectPtr& v) const{
    auto copyExpr = *this;
    if(copyExpr.leftExpr->instanceOf<IExpression>()){
      copyExpr.leftExpr = copyExpr.leftExpr->to<IExpression>().simplify(false);
    }

    AddExpression polynom(*leftExpr);
    auto maxPow = polynom.getPow();

    if(!maxPow->is<Integer>() || maxPow->to<Integer>() > Integer(2)){
      return {};
    }

    std::vector<MathObjectPtr> coefficients;

    auto pow = maxPow->to<Integer>();

    for(int i = 0; i <= maxPow->to<Integer>();i++){
      coefficients.emplace_back(polynom.getPowCoefficient(Integer(i).clone()));
      auto coef = coefficients.at(i)->toString();
      auto b = coef;
    }

    std::vector<MathObjectPtr> results;  
    if(coefficients.size() == 2){
      results.emplace_back(Neg()(Div()(*coefficients.at(0), *coefficients.at(1))).simplify(false));
      return results;
    }
    if(coefficients.size() == 3){
      auto discr = Sub()(*fintamath::pow(*coefficients.at(1), Integer(2)).simplify(false), *mul(Integer(4), *coefficients.at(0), *coefficients.at(2)).simplify(false)).simplify(false);

      auto discrStr = discr->toString();
      auto aStr = coefficients.at(2)->toString();
      auto cStr = coefficients.at(0)->toString();
      auto bStr = coefficients.at(1)->toString();

      if(discr->instanceOf<IComparable>() && discr->to<IComparable>() < Integer(0)){
        return {};
      }

      auto sqrt_D = sqrt(*discr).simplify(false);
      auto minus_B = Neg()(*coefficients.at(1)).simplify(false);
      auto two_A = mul(*coefficients.at(2), Integer(2)).simplify(false);

      auto a = sqrt_D->toString();
      auto dis = discr->toString();
      auto two_a = two_A->toString();
      auto minusB =minus_B->toString();

      auto x1 = Div()(*Sub()(*minus_B, *sqrt_D).simplify(false), *two_A).simplify(false);
      auto x2 = Div()(*add(*minus_B, *sqrt_D).simplify(false), *two_A).simplify(false);

      results.emplace_back(x1->clone());
      results.emplace_back(x2->clone());

      return results;
    }
    return results;
  }

  

  bool EqvExpression::detectOneVariable(Variable &v) const {
    if(leftExpr->is<Variable>()){
      v = leftExpr->to<Variable>();
      return true;
    }
    if(leftExpr->instanceOf<IExpression>()){
      auto variables = leftExpr->to<IExpression>().getVariables();
      if(variables.empty()){
        return false;
      }
      v = variables.at(0)->to<Variable>();
      for(const auto& var : variables){
        if(var->toString() != v.toString()){
          return false;
        }
      }
      return true;
    }
  }
}