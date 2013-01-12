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

#include "Log.hh"
#include "Functions.hh"
#include "dsAssert.hh"
#include <sstream>

namespace Eqo {
Log::Log(EqObjPtr var) : EquationObject(LOG_OBJ), value(var)
{
}

std::string Log::createStringValue() const
{
    std::ostringstream os;
    os << "log(" << value << ")";
    return std::string(os.str());
}

EqObjPtr Log::Derivative(EqObjPtr foo)
{
  EqObjPtr ret;
  if (value->getType() == CONST_OBJ)
  {
    ret = con(0.0);
  }
  else
  {
    ret = value->Derivative(foo)*pow(value,EqObjPtr(new Constant(-1.0)));
  }

  return ret;
}

EqObjPtr Log::Simplify()
{
   if (value->isOne())
      return con(0);

   ///log(exp(x))) = x;
   if (value->getType() == EXPONENT_OBJ)
   {
      Exponent *Y = dynamic_cast<Exponent *>(value.get());
      return (Y->value);
   }

   ///log(exp(x))) = x;
   if (value->getType() == EXPONENT_OBJ)
   {
      Exponent *Y = dynamic_cast<Exponent *>(value.get());
      return (Y->value);
   }

   ///log(pow(x,y))) = y*log(x);
   if (value->getType() == POW_OBJ)
   {
      Pow *Y = dynamic_cast<Pow *>(value.get());
      return (Y->exponent * log(Y->base));
   }

   return log(value->Simplify());
}

EqObjPtr Log::CombineProduct(std::vector<EqObjPtr> y)
{
   if (y.empty())
     return shared_from_this();

   y.push_back(shared_from_this());
   return EqObjPtr(new Product(y));
}

/**
 * now just return original std::vector
 * in the future, log(x)+log(y) = log(x*y)
 */
EqObjPtr Log::CombineAdd(std::vector<EqObjPtr> y)
{
   if (y.empty())
      return shared_from_this();

   y.push_back(shared_from_this());
   return EqObjPtr(new Add(y));
}

bool Log::isZero()
{
   return false;
}

bool Log::isOne()
{
   return false;
}

EqObjPtr Log::getScale()
{
   return con(1);
}

EqObjPtr Log::getUnscaledValue()
{
   return shared_from_this();
}

double Log::getSign()
{
    return 1.0;
}

EqObjPtr Log::getUnsignedValue()
{
   return shared_from_this();
}

EqObjPtr Log::clone()
{
    EquationObject *n = new Log(value->clone());
    return EqObjPtr(n);
}

EqObjPtr Log::subst(const std::string &str, EqObjPtr eqo)
{
    if (str == this->stringValue())
        return eqo;
    else
        return log(value->subst(str, eqo));
}

EqObjPtr Log::expand()
{
    return log(value->expand());
}
}

