/***
Copyright 2012 Devsim LLC

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
***/
#include "EngineAPI.hh"
#include "LogicalFunc.hh"
#include "IfElse.hh"
#include "Functions.hh"
#include "Context.hh"
#include "mcModel.hh"

namespace EngineAPI {
Eqo::EqObjPtr createUnaryLogical(const std::string &unaryOp, Eqo::EqObjPtr arg)
{
  return Eqo::EqObjPtr(new Eqo::UnaryLogical(unaryOp, arg));
}

Eqo::EqObjPtr createBinaryLogical(const std::string &unaryOp, Eqo::EqObjPtr arg1, Eqo::EqObjPtr arg2)
{
  return Eqo::EqObjPtr(new Eqo::BinaryLogical(unaryOp, arg1, arg2));
}

Eqo::EqObjPtr createIfObj(Eqo::EqObjPtr test, Eqo::EqObjPtr result)
{
  return Eqo::EqObjPtr(new Eqo::IfObj(test, result));
}

Eqo::EqObjPtr createIfElseObj(Eqo::EqObjPtr test, Eqo::EqObjPtr left, Eqo::EqObjPtr right)
{
  return Eqo::EqObjPtr(new Eqo::IfElseObj(test, left, right));
}

/// Non member functions for intuitive math operations
Eqo::EqObjPtr operator* (Eqo::EqObjPtr x, Eqo::EqObjPtr y)
{
  return Eqo::operator*(x, y);
}

Eqo::EqObjPtr pow (Eqo::EqObjPtr x, Eqo::EqObjPtr y);

Eqo::EqObjPtr operator/ (Eqo::EqObjPtr x, Eqo::EqObjPtr y)
{
  return Eqo::operator/(x, y);
}

Eqo::EqObjPtr operator+ (Eqo::EqObjPtr x, Eqo::EqObjPtr y)
{
  return Eqo::operator+(x, y);
}

Eqo::EqObjPtr operator- (Eqo::EqObjPtr x, Eqo::EqObjPtr y)
{
  return Eqo::operator-(x, y);
}

Eqo::EqObjPtr exp (Eqo::EqObjPtr x)
{
  return Eqo::exp(x);
}

Eqo::EqObjPtr pow (Eqo::EqObjPtr x, Eqo::EqObjPtr y)
{
  return Eqo::pow(x, y);
}

Eqo::EqObjPtr log (Eqo::EqObjPtr x)
{
  return Eqo::log(x);
}

Eqo::EqObjPtr diff(Eqo::EqObjPtr x, Eqo::EqObjPtr y)
{
   return Eqo::diff(x, y);
}

Eqo::EqObjPtr con(double x)
{
  return Eqo::con(x);
}

Eqo::EqObjPtr mod(const char *x)
{
  return Eqo::mod(x);
}

Eqo::EqObjPtr mod(const std::string &x)
{
  return Eqo::mod(x);
}

Eqo::EqObjPtr var(const char *x)
{
  return Eqo::var(x);
}

Eqo::EqObjPtr var(const std::string &x)
{
  return Eqo::var(x);
}

Eqo::EqObjPtr sqrt(Eqo::EqObjPtr x)
{
  return Eqo::sqrt(x);
}

Eqo::EqObjPtr reciprocal_sqrt(Eqo::EqObjPtr x)
{
  return Eqo::reciprocal_sqrt(x);
}

/// how we print things
std::ostream & operator<< (std::ostream &os, Eqo::EqObjPtr foo)
{
  return Eqo::operator<<(os, foo);
}

/// keeps simplifying expression until string value doesn't change
Eqo::EqObjPtr Simplify(Eqo::EqObjPtr x)
{
  return Eqo::Simplify(x);
}

Eqo::EqObjPtr getConstantFactor(Eqo::EqObjPtr x)
{
  return Eqo::getConstantFactor(x);
}

Eqo::EqObjPtr Expand(Eqo::EqObjPtr x)
{
  return Eqo::Expand(x);
}

Eqo::EqObjPtr getUnscaledValue(Eqo::EqObjPtr x)
{
  return Eqo::getUnscaledValue(x);
}

Eqo::EqObjPtr getUnsignedValue(Eqo::EqObjPtr x)
{
  return Eqo::getUnsignedValue(x);
}

Eqo::EqObjPtr getSign(Eqo::EqObjPtr x)
{
  return Eqo::getSign(x);
}

/// Sorts in order of constants, variables, then other objects
void SortEqVector(std::vector<Eqo::EqObjPtr> &v1)
{
  Eqo::SortEqVector(v1);
}

Eqo::EqObjPtr subst(Eqo::EqObjPtr a, Eqo::EqObjPtr b, Eqo::EqObjPtr c)
{
  return Eqo::subst(a, b, c);
}

Eqo::EqObjPtr getNegation(Eqo::EqObjPtr x)
{
  return Eqo::getNegation(x);
}

bool isBinaryFunction(const std::string &str)
{
  return Eqo::getBinaryFuncPtr(str) != NULL;
}

bool isUnaryFunction(const std::string &str)
{
  return Eqo::getUnaryFuncPtr(str) != NULL;
}
EqBinaryFuncPtr getBinaryFuncPtr(const std::string &str)
{
  return Eqo::getBinaryFuncPtr(str);
}

EqUnaryFuncPtr DLL_PUBLIC getUnaryFuncPtr(const std::string &str)
{
  return Eqo::getUnaryFuncPtr(str);
}

std::string DLL_PUBLIC getName(Eqo::EqObjPtr x)
{
  std::string ret;
  return x->getName();
  return ret;
}

std::string DLL_PUBLIC getType(Eqo::EqObjPtr x)
{
  std::string ret;
  ret = Eqo::EqObjNames[x->getType()];
  return ret;
}

EqObjType DLL_PUBLIC getEnumeratedType(Eqo::EqObjPtr x)
{
  return EqObjType(x->getType());
}

std::string DLL_PUBLIC getStringValue(Eqo::EqObjPtr x)
{
  std::string ret;
  return x->stringValue();
  return ret;
}

double DLL_PUBLIC getDoubleValue(Eqo::EqObjPtr x)
{
  assert(x->getType() == Eqo::CONST_OBJ);
  return dynamic_cast<Eqo::Constant *>(x.get())->getDoubleValue();
}

std::set<std::string> DLL_PUBLIC getReferencedType(Eqo::EqObjPtr x, EqObjType t)
{
  return x->getReferencedType(Eqo::EqObjType(t));
}

std::vector<Eqo::EqObjPtr> DLL_PUBLIC getArgs(Eqo::EqObjPtr x)
{
  return x->getArgs();
}

void DLL_PUBLIC SetModelListCallBack(inModelListCallback_ptr x)
{
  Context &context = Context::GetInstance();
  context.SetModelListCallBack(x);
}

void DLL_PUBLIC SetDerivativeRule(modelDerivativeRule_ptr x)
{
  Context &context = Context::GetInstance();
  context.SetDerivativeRule(x);
}
}

