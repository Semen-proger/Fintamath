#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/functions/Functions.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/literals/Variable.hpp"

#include <fstream>

using namespace fintamath;

TEST(ExpressionTests, constructorTest) {
  EXPECT_EQ(Expression().toString(), "0");
}

TEST(ExpressionTests, moveTest) {
  auto a = Expression("1+2");
  EXPECT_EQ(a.toString(), "3");
  auto b = std::move(a);
  EXPECT_TRUE(b.toString() == "3" && a.toString() == "0");
  a = std::move(b);
  EXPECT_TRUE(a.toString() == "3" && b.toString() == "0");
}

TEST(ExpressionTests, copyTest) {
  auto a = Expression("1+2");
  auto b = a;
  EXPECT_TRUE(a == b && &a != &b);
}

TEST(ExpressionTests, stingConstructorTest) {
  EXPECT_EQ(Expression("2").toString(), "2");
  EXPECT_EQ(Expression("2 + 2").toString(), "4");
  EXPECT_EQ(Expression("-2 + 3").toString(), "1");
  EXPECT_EQ(Expression("2 * 2").toString(), "4");
  EXPECT_EQ(Expression("1 / 3").toString(), "1/3");
  EXPECT_EQ(Expression("0 / 3").toString(), "0");
  EXPECT_EQ(Expression("2 ^ 2").toString(), "4");

  EXPECT_EQ(Expression("0^1").toString(), "0");
  EXPECT_EQ(Expression("2^0").toString(), "1");
  EXPECT_EQ(Expression("(-7)^10").toString(), "282475249");
  EXPECT_EQ(Expression("2^0").toString(), "1");

  EXPECT_EQ(Expression("0.001-0.002").toString(), "-1/1000");
  EXPECT_EQ(Expression("(0.004)/(0.002+0.002)").toString(), "1");

  EXPECT_EQ(Expression("2 + 2 * 2").toString(), "6");
  EXPECT_EQ(Expression("2^2^2^2").toString(), "65536");
  EXPECT_EQ(Expression("(2 + 2) * 2").toString(), "8");
  EXPECT_EQ(Expression("(2-2)").toString(), "0");
  EXPECT_EQ(Expression("(2 + 2) / (2 ^ 2 - 2) * 2").toString(), "4");
  EXPECT_EQ(Expression("((((2))))").toString(), "2");
  EXPECT_EQ(Expression("(((((2 + 2) + 2) + 2) + 2) + 2)").toString(), "12");
  EXPECT_EQ(Expression("(((2 ^ 2)^2))").toString(), "16");

  EXPECT_EQ(Expression("--5").toString(), "5");
  EXPECT_EQ(Expression("5*-3").toString(), "-15");

  EXPECT_EQ(Expression("5!").toString(), "120");
  EXPECT_EQ(Expression("-1!").toString(), "-1");
  EXPECT_EQ(Expression("-100!").toString(),
            "-933262154439441526816992388562667004907159682643816214685929638952175999932299156089414639761565182862536"
            "97920827223758251185210916864000000000000000000000000");
  EXPECT_EQ(Expression("5!!").toString(), "15");

  EXPECT_EQ(Expression("(2)!").toString(), "2");

  EXPECT_EQ(Expression("-(-(-(-(-(-(-(-a)))))))").toString(), "a");
  EXPECT_EQ(Expression("a+a").toString(), "2*a");
  EXPECT_EQ(Expression("a-a").toString(), "0");
  EXPECT_EQ(Expression("(a+b)-b").toString(), "a");
  EXPECT_EQ(Expression("(a+b)*(a+b)+a*b*c-c*a*b+b*a").toString(), "a^2+b^2+3*a*b");

  EXPECT_EQ(Expression("ln cos sin a").toString(), "n^2*s^2*a*c*i*l*o");
  EXPECT_EQ(Expression("(a+b)*(a+b)/(a+b)").toString(), "a+b");

  EXPECT_EQ(Expression("+5").toString(), "5");
  EXPECT_EQ(Expression("+a").toString(), "a");

  // TODO: EqvExpr
  // EXPECT_EQ(Expression("a=a").toString(), "1");
  // EXPECT_EQ(Expression("a+a=2*a").toString(), "1");

  EXPECT_EQ(Expression("(a+b)^2").toString(), "a^2+b^2+2*a*b");
  EXPECT_EQ(Expression("(a+b)^3").toString(), "a^3+b^3+3*a^2*b+3*b^2*a");
  EXPECT_EQ(Expression("1*(a+b)^3").toString(), "a^3+b^3+3*a^2*b+3*b^2*a");
  EXPECT_EQ(Expression("(a+b)^4").toString(), "a^4+b^4+4*a^3*b+4*b^3*a+6*a^2*b^2");
  EXPECT_EQ(Expression("(a+3)/(b+2)").toString(), "(a+3)/(b+2)");
  EXPECT_EQ(Expression("b/a*(a+3)/(b+2)").toString(), "(3*b+a*b)/(2*a+a*b)");
  EXPECT_EQ(Expression("(5+b)/a*(a+3)/(b+2)").toString(), "(3*b+5*a+a*b+15)/(2*a+a*b)");

  EXPECT_EQ(Expression("e ").toString(),
            "2.7182818284590452353602874713526624977572470936999595749669676277240766303535476");
  EXPECT_EQ(Expression("pi").toString(),
            "3.141592653589793238462643383279502884197169399375105820974944592307816406286209");

  EXPECT_EQ(Expression("abs(-5)").toString(), "5");
  EXPECT_EQ(Expression("abs((-5))").toString(), "5");

  EXPECT_EQ(Expression("sqrt144").toString(), "12");
  EXPECT_EQ(Expression("sqrt0").toString(), "0");
  EXPECT_EQ(Expression("exp100").toString(),
            "26881171418161354484126255515800135873611118.773741922415191608615280287034909565");

  EXPECT_EQ(Expression("e^101").toString(),
            "73070599793680672726476826340615135890078390.083960707616445859670987728609198428");
  EXPECT_EQ(Expression("e^(-101)").toString(), "1.3685394711738530002470557302322944177986775531612023009807438134142551921153897*10^-44");

  EXPECT_EQ(Expression("log(e,e)").toString(), "1");
  EXPECT_EQ(Expression("log(2, 256)").toString(), "8");
  EXPECT_EQ(Expression("log(pi, pi^10)").toString(), "10");
  EXPECT_EQ(Expression("log(e,e^3)").toString(), "3");

  EXPECT_EQ(Expression("ln3").toString(),
            "1.098612288668109691395245236922525704647490557822749451734694333637494293218609");
  EXPECT_EQ(Expression("ln2").toString(),
            "0.69314718055994530941723212145817656807550013436025525412068000949339362196969472");
  EXPECT_EQ(Expression("ln100").toString(),
            "4.605170185988091368035982909368728415202202977257545952066655801935145219354705");
  EXPECT_EQ(Expression("ln(e)").toString(), "1");

  EXPECT_EQ(Expression("lg99").toString(),
            "1.9956351945975499153402557777532548601069599188478448242562702992902113378005716");
  EXPECT_EQ(Expression("lg100").toString(), "2");

  EXPECT_EQ(Expression("lb100").toString(),
            "6.6438561897747246957406388589787803517296627860491612241095127916318695532172504");
  EXPECT_EQ(Expression("lb4").toString(), "2");

  EXPECT_EQ(Expression("sin10").toString(),
            "-0.54402111088936981340474766185137728168364301291622389157418401261675720964049343");
  EXPECT_EQ(Expression("cos10").toString(),
            "-0.83907152907645245225886394782406483451993016513316854683595373104879258686627077");
  EXPECT_EQ(Expression("tan10").toString(),
            "0.6483608274590866712591249330098086768168743429837249756336279673958556003746239");
  EXPECT_EQ(Expression("cot10").toString(),
            "1.5423510453569200482774693556824293113206672064019624909194716061981945043136768");

  EXPECT_EQ(Expression("asin0.9").toString(),
            "1.1197695149986341866866770558453996158951621864033028823756818639144375371065333");
  EXPECT_EQ(Expression("acos0.9").toString(),
            "0.45102681179626243254464463579435182620342251328425002811179043223947066603657116");
  EXPECT_EQ(Expression("atan10").toString(),
            "1.4711276743037345918528755717617308518553063771832382624719635193438804556955538");
  EXPECT_EQ(Expression("acot10").toString(),
            "0.099668652491162027378446119878020590243278322504314648015508776810027747447550654");

  EXPECT_EQ(Expression("((2))*sqrt2").toString(),
            "2.8284271247461900976033774484193961571393437507538961463533594759814649569242141");
  EXPECT_EQ(Expression("sqrt2*((2))").toString(),
            "2.8284271247461900976033774484193961571393437507538961463533594759814649569242141");

  EXPECT_EQ(Expression("sin(1)^2").toString(),
            "0.70807341827357119349878411475038109488300038553777244537757498689098246806203958");
  EXPECT_EQ(Expression("sin(-1)^2").toString(),
            "0.70807341827357119349878411475038109488300038553777244537757498689098246806203958");
  EXPECT_EQ(Expression("sin1^2").toString(),
            "0.70807341827357119349878411475038109488300038553777244537757498689098246806203958");
  EXPECT_EQ(Expression("sin(10^30)").toString(),
            "-0.090116901912138058030386428952987330274396332993043449885460666579773983476795775");
  EXPECT_EQ(Expression("sin(1)^2+cos(1)^2").toString(), "1");
  EXPECT_EQ(Expression("sin(pi/3)").toString(),
            "0.86602540378443864676372317075293618347140262690519031402790348972596650845440002");
  EXPECT_EQ(Expression("cos(pi/3)").toString(), "0.5");

  EXPECT_EQ(Expression("lne").toString(),
            "2.7182818284590452353602874713526624977572470936999595749669676277240766303535476*l*n");
  EXPECT_EQ(Expression("lncossine").toString(),
            "2.7182818284590452353602874713526624977572470936999595749669676277240766303535476*n^2*s^2*c*i*l*o");

  EXPECT_EQ(Expression("e^101-e^101").toString(), "0");
  EXPECT_EQ(Expression("ln(e^e) / ln(e^e) - 1").toString(), "0");

  EXPECT_EQ(Expression("sqrt4!").toString(), "2");
  EXPECT_EQ(Expression("(sqrt4)!").toString(), "2");
  EXPECT_EQ(Expression("sqrt4*2!").toString(), "4");
  EXPECT_EQ(Expression("2!*e").toString(),
            "5.4365636569180904707205749427053249955144941873999191499339352554481532607070952");
  EXPECT_EQ(Expression("e*2!").toString(),
            "5.4365636569180904707205749427053249955144941873999191499339352554481532607070952");

  EXPECT_EQ(Expression("sqrt((1-cos(2*(pi/3)))/2)").toString(),
            "0.86602540378443864676372317075293618347140262690519031402790348972596650845440002");
  EXPECT_EQ(Expression("2*sqrt((1-cos(2*(pi/3)))/2)*cos(pi/3)").toString(),
            "0.86602540378443864676372317075293618347140262690519031402790348972596650845440002");
}

TEST(ExpressionTests, stringConstructorNegativeTest) {
  EXPECT_ANY_THROW(Expression(""));
  EXPECT_ANY_THROW(Expression("1+"));
  EXPECT_ANY_THROW(Expression("1-"));
  EXPECT_ANY_THROW(Expression("1*"));
  EXPECT_ANY_THROW(Expression("1/"));
  EXPECT_ANY_THROW(Expression(" +   "));
  EXPECT_ANY_THROW(Expression("(1+2))"));
  EXPECT_ANY_THROW(Expression("5-*3"));
  EXPECT_ANY_THROW(Expression("((()()))"));
  EXPECT_ANY_THROW(Expression("2.a"));
  EXPECT_ANY_THROW(Expression("2.2.2"));
  EXPECT_ANY_THROW(Expression("--"));
  EXPECT_ANY_THROW(Expression("."));
  EXPECT_ANY_THROW(Expression(","));
  EXPECT_ANY_THROW(Expression("/"));
  EXPECT_ANY_THROW(Expression(";"));
  EXPECT_ANY_THROW(Expression("\'"));
  EXPECT_ANY_THROW(Expression("["));
  EXPECT_ANY_THROW(Expression("]"));
  EXPECT_ANY_THROW(Expression("!"));
  EXPECT_ANY_THROW(Expression("@"));
  EXPECT_ANY_THROW(Expression("\""));
  EXPECT_ANY_THROW(Expression("#"));
  EXPECT_ANY_THROW(Expression("№"));
  EXPECT_ANY_THROW(Expression("%"));
  EXPECT_ANY_THROW(Expression(":"));
  EXPECT_ANY_THROW(Expression("?"));
  EXPECT_ANY_THROW(Expression("*"));
  EXPECT_ANY_THROW(Expression("("));
  EXPECT_ANY_THROW(Expression(")"));
  EXPECT_ANY_THROW(Expression("-"));
  EXPECT_ANY_THROW(Expression("+"));
  EXPECT_ANY_THROW(Expression("$"));
  EXPECT_ANY_THROW(Expression("^"));
  EXPECT_ANY_THROW(Expression("&"));
  EXPECT_ANY_THROW(Expression("_"));
  EXPECT_ANY_THROW(Expression("[1+1]"));
  EXPECT_ANY_THROW(Expression("{1}"));
  EXPECT_ANY_THROW(Expression("(1"));
  EXPECT_ANY_THROW(Expression("(((2)"));
  EXPECT_ANY_THROW(Expression("(((2))"));
  EXPECT_ANY_THROW(Expression("((2)))"));
  EXPECT_ANY_THROW(Expression("(2)))"));
  EXPECT_ANY_THROW(Expression("(2"));
  EXPECT_ANY_THROW(Expression("((2)"));
  EXPECT_ANY_THROW(Expression("((2"));
  EXPECT_ANY_THROW(Expression("(()())"));
  EXPECT_ANY_THROW(Expression("((((()))))"));
  EXPECT_ANY_THROW(Expression("((((2)((2))))"));
  EXPECT_ANY_THROW(Expression("!2"));
  EXPECT_ANY_THROW(Expression("!!2"));
  EXPECT_ANY_THROW(Expression("!2!!"));
  EXPECT_ANY_THROW(Expression("!(2"));
  EXPECT_ANY_THROW(Expression("!(2)"));
  EXPECT_ANY_THROW(Expression("2)!"));
  EXPECT_ANY_THROW(Expression("1/0"));
  EXPECT_ANY_THROW(Expression("0^0"));
  EXPECT_ANY_THROW(Expression("sin(2))!"));

  EXPECT_ANY_THROW(Expression("(-1)!"));
  EXPECT_ANY_THROW(Expression("(2/3)!"));
  EXPECT_ANY_THROW(Expression("(-1)!!"));
  EXPECT_ANY_THROW(Expression("(2/3)!!"));
  EXPECT_ANY_THROW(Expression("e!"));
  EXPECT_ANY_THROW(Expression("sqrt(-1)"));
  EXPECT_ANY_THROW(Expression("ln(0)"));
  EXPECT_ANY_THROW(Expression("ln(-1)"));
  EXPECT_ANY_THROW(Expression("log(-1, 1)"));
  EXPECT_ANY_THROW(Expression("log(0, 1)"));
  EXPECT_ANY_THROW(Expression("log(1, 0)"));
  EXPECT_ANY_THROW(Expression("lb(-1)"));
  EXPECT_ANY_THROW(Expression("lg(-1)"));
  EXPECT_ANY_THROW(Expression("(-1)^(2/3)"));
  EXPECT_ANY_THROW(Expression("tan(pi/2)"));
  EXPECT_ANY_THROW(Expression("cot(0)"));
  EXPECT_ANY_THROW(Expression("asin(2)"));
  EXPECT_ANY_THROW(Expression("acos(2)"));
  EXPECT_ANY_THROW(Expression("tan(3/2*pi)"));
  EXPECT_ANY_THROW(Expression("cot(2*pi)"));
}

TEST(ExpressionTests, solveTest) {
}

TEST(ExpressionTests, toStringTest) {
  EXPECT_EQ(Expression("a^-3").toString(), "a^(-3)");
}

TEST(ExpressionTests, toStringPrecision) {
  EXPECT_EQ(Expression("10^10000").toString(8), "1*10^10000");
  EXPECT_EQ(Expression("9^10000").toString(8), "2.6613034*10^9542");
  EXPECT_EQ(Expression("sin(e)").toString(16), "0.4107812905029087");
  EXPECT_EQ(Expression("sin(sin(e))").toString(30), "0.39932574404189139297067052142");
}
