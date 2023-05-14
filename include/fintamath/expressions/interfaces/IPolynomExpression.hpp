#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class IPolynomExpression : virtual public IExpression {
public:
  std::string toString() const final;

  std::shared_ptr<IFunction> getFunction() const final;

  ArgumentsPtrVector getChildren() const final;

  void setChildren(const ArgumentsPtrVector &childVect) final;

  virtual void addElement(const ArgumentPtr &element) = 0;

protected:
  using SimplifyFunction =
      std::function<ArgumentPtr(const IFunction &, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild)>;

  using SimplifyFunctionsVector = std::vector<SimplifyFunction>;

  virtual SimplifyFunctionsVector getFunctionsForSimplify() const;

  virtual SimplifyFunctionsVector getFunctionsForPreSimplify() const;

  virtual SimplifyFunctionsVector getFunctionsForPostSimplify() const;

  virtual std::string operatorChildToString(const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const;

  /**
   * @brief
   *
   * @param lhs
   * @param rhs
   * @return -1 if we should swap the arguments
   * @return  1 if we should not swap the arguments
   * @return  0 if this comparator fails
   */
  virtual int comparator(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const;

  ArgumentPtr simplify() const final;

  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;

  virtual bool isTermsOrderInversed() const;

  virtual bool isComparableOrderInversed() const;

  virtual bool isUnaryOperatorsOrderInversed() const;

private:
  void preSimplifyRec();

  void postSimplifyRec();

  void simplifyRec();

  ArgumentPtr useSimplifyFunctions(const SimplifyFunctionsVector &simplFuncs, size_t lhsChildPos,
                                   size_t rhsChildPos) const;

  void sort();

  /**
   * @brief
   *
   * @param lhs
   * @param rhs
   * @return -1 if we should swap the arguments
   * @return  1 if we should not swap the arguments
   * @return  0 if this comparator fails
   */
  int comparatorPolynomsAndBinaryFunctions(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const;

  /**
   * @brief
   *
   * @param lhsExpr
   * @param rhsExpr
   * @return -1 if we should swap the arguments
   * @return  1 if we should not swap the arguments
   * @return  0 if this comparator fails
   */
  int comparatorFunctions(const std::shared_ptr<const IExpression> &lhsExpr,
                          const std::shared_ptr<const IExpression> &rhsExpr) const;

  /**
   * @brief
   *
   * @param lhs
   * @param rhs
   * @return -1 if we should swap the arguments
   * @return  1 if we should not swap the arguments
   * @return  0 if this comparator fails
   */
  int comparatorExpressionAndNonExpression(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const;

  /**
   * @brief
   *
   * @param lhs
   * @param rhs
   * @return -1 if we should swap the arguments
   * @return  1 if we should not swap the arguments
   * @return  0 if this comparator fails
   */
  int comparatorNonExpressions(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const;

  /**
   * @brief
   *
   * @param lhsChildren
   * @param rhsChildren
   * @return -1 if we should swap the arguments
   * @return  1 if we should not swap the arguments
   * @return  0 if this comparator fails
   */
  int comparatorChildren(const ArgumentsPtrVector &lhsChildren, const ArgumentsPtrVector &rhsChildren,
                         bool ignoreUnaryIfPossible = false) const;

  /**
   * @brief
   *
   * @param lhsChildren
   * @param rhsChildren
   * @return -1 if we should swap the arguments
   * @return  1 if we should not swap the arguments
   * @return  0 if this comparator fails
   */
  int comparatorChildren(const ArgumentPtr &lhs, const ArgumentPtr &rhs, bool ignoreUnaryIfPossible = false) const;

  /**
   * @brief
   *
   * @param lhs
   * @param rhs
   * @return -1 if we should swap the arguments
   * @return  1 if we should not swap the arguments
   * @return  0 if this comparator fails
   */
  static int comparatorVariables(const std::vector<Variable> &lhsVars, const std::vector<Variable> &rhsVars,
                                 bool isTermsOrderInversed);

  static ArgumentPtr findFirstPolynomChild(const ArgumentPtr &rhs);

  static std::vector<Variable> getVariables(const ArgumentPtr &rhs);

protected:
  std::shared_ptr<IFunction> func;

  ArgumentsPtrVector children;
};

template <typename Derived>
class IPolynomExpressionCRTP : virtual public IExpressionCRTP<Derived>, virtual public IPolynomExpression {
public:
  explicit IPolynomExpressionCRTP(const IFunction &inFunc, const ArgumentsPtrVector &inChildren) {
    this->func = cast<IFunction>(inFunc.clone());

    for (const auto &child : inChildren) {
      addElement(child);
    }
  }

  void addElement(const ArgumentPtr &element) final {
    ArgumentPtr elem = element;
    compressChild(elem);

    ArgumentsPtrVector elemPolynom;

    if (auto expr = cast<Derived>(elem)) {
      elemPolynom = expr->children;
    }

    if (!elemPolynom.empty()) {
      for (auto &child : elemPolynom) {
        children.emplace_back(child);
      }
    }
    else {
      children.emplace_back(elem);
    }
  }
};

}