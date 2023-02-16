#include "fintamath/numbers/RealFunctions.hpp"

#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"
#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include "fintamath/numbers/NumberImpls.hpp"

namespace fintamath {

Real abs(const Real &rhs) {
  if (rhs < 0) {
    return -rhs;
  }

  return rhs;
}

Real sqrt(const Real &rhs) {
  if (rhs < 0) {
    throw UndefinedFunctionException("sqrt", {rhs.toString()});
  }

  return RealImpl(sqrt(rhs.getImpl()->v));
}

Real pow(const Real &lhs, const Real &rhs) {
  if (lhs.isNearZero() && rhs.isNearZero()) {
    throw UndefinedBinaryOpearatorException("^", lhs.toString(), rhs.toString());
  }
  if (lhs < 0 && !is<Integer>(rhs.toMinimalObject())) {
    throw UndefinedBinaryOpearatorException("^", lhs.toString(), rhs.toString());
  }

  RealImpl res = RealImpl(pow(lhs.getImpl()->v, rhs.getImpl()->v));

  if (res.v.backend().isinf() || res.v.backend().isnan()) {
    throw UndefinedBinaryOpearatorException("^", lhs.toString(), rhs.toString());
  }

  return res;
}

Real exp(const Real &rhs) {
  return RealImpl(exp(rhs.getImpl()->v));
}

Real log(const Real &lhs, const Real &rhs) {
  try {
    return ln(rhs) / ln(lhs);
  } catch (const UndefinedException &) {
    throw UndefinedFunctionException("log", {lhs.toString(), rhs.toString()});
  }
}

Real ln(const Real &rhs) {
  if (rhs <= 0) {
    throw UndefinedFunctionException("ln", {rhs.toString()});
  }

  return RealImpl(log(rhs.getImpl()->v));
}

Real lb(const Real &rhs) {
  if (rhs <= 0) {
    throw UndefinedFunctionException("lb", {rhs.toString()});
  }

  return RealImpl(log2(rhs.getImpl()->v));
}

Real lg(const Real &rhs) {
  if (rhs <= 0) {
    throw UndefinedFunctionException("lg", {rhs.toString()});
  }

  return RealImpl(log10(rhs.getImpl()->v));
}

Real sin(const Real &rhs) {
  Real res = RealImpl(sin(rhs.getImpl()->v));

  if (res.isNearZero()) {
    return 0;
  }

  return res;
}

Real cos(const Real &rhs) {
  Real res = RealImpl(cos(rhs.getImpl()->v));

  if (res.isNearZero()) {
    return 0;
  }

  return res;
}

Real tan(const Real &rhs) {
  try {
    return sin(rhs) / cos(rhs);
  } catch (const UndefinedException &) {
    throw UndefinedFunctionException("tan", {rhs.toString()});
  }
}

Real cot(const Real &rhs) {
  try {
    return cos(rhs) / sin(rhs);
  } catch (const UndefinedException &) {
    throw UndefinedFunctionException("cot", {rhs.toString()});
  }
}

Real asin(const Real &rhs) {
  RealImpl::Backend res = asin(rhs.getImpl()->v);

  if (res.backend().isnan()) {
    throw UndefinedFunctionException("asin", {rhs.toString()});
  }

  return RealImpl(res);
}

Real acos(const Real &rhs) {
  RealImpl::Backend res = acos(rhs.getImpl()->v);

  if (res.backend().isnan()) {
    throw UndefinedFunctionException("acos", {rhs.toString()});
  }

  return RealImpl(res);
}

Real atan(const Real &rhs) {
  return RealImpl(atan(rhs.getImpl()->v));
}

Real acot(const Real &rhs) {
  Real res = PI_NUM / 2;

  if (rhs < 0) {
    res = -res;
  }

  return res - atan(rhs);
}

Real sinh(const Real &rhs) {
  return RealImpl(sinh(rhs.getImpl()->v));
}

Real cosh(const Real &rhs) {
  return RealImpl(cosh(rhs.getImpl()->v));
}

Real tanh(const Real &rhs) {
  return RealImpl(tanh(rhs.getImpl()->v));
}

Real coth(const Real &rhs) {
  try {
    return 1 / tanh(rhs);
  } catch (const UndefinedException &) {
    throw UndefinedFunctionException("coth", {rhs.toString()});
  }
}

Real asinh(const Real &rhs) {
  return ln(sqrt(rhs * rhs + 1) + rhs);
}

Real acosh(const Real &rhs) {
  try {
    return ln(rhs + sqrt(rhs - 1) * sqrt(rhs + 1));
  } catch (const UndefinedException &) {
    throw UndefinedFunctionException("acoth", {rhs.toString()});
  }
}

Real atanh(const Real &rhs) {
  try {
    return (ln(1 + rhs) - ln(1 - rhs)) / 2;
  } catch (const UndefinedException &) {
    throw UndefinedFunctionException("acoth", {rhs.toString()});
  }
}

Real acoth(const Real &rhs) {
  try {
    return (ln(1 + 1 / rhs) - ln(1 - 1 / rhs)) / 2;
  } catch (const UndefinedException &) {
    throw UndefinedFunctionException("acoth", {rhs.toString()});
  }
}

}
