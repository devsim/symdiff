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

#include "Variable.hh"
#include "Functions.hh"
#include "dsAssert.hh"
#include <sstream>
namespace Eqo {
EqObjPtr Variable::getScale()
{
   return con(1);
}

EqObjPtr Variable::getUnscaledValue()
{
   return shared_from_this();
}

double Variable::getSign()
{
    return 1.0;
}

EqObjPtr Variable::getUnsignedValue()
{
   return shared_from_this();
}


Variable::Variable(std::string var) : EquationObject(VARIABLE_OBJ), value(var)
{
}

std::string Variable::createStringValue() const
{
    return value;
}

EqObjPtr Variable::Derivative(EqObjPtr foo)
{
    if (foo->stringValue() == value)
        return con(1.0);
    else
        return con(0.0);
}

EqObjPtr Variable::Simplify()
{
   return shared_from_this();
}

/**
 * This function may never be called if variables
 * are turned into Pow's.
 */
EqObjPtr Variable::CombineProduct(std::vector<EqObjPtr> y)
{
   if (y.empty())
      return shared_from_this();

   y.push_back(shared_from_this());
   return EqObjPtr(new Product(y));
}

EqObjPtr Variable::CombineAdd(std::vector<EqObjPtr> y)
{
   if (y.empty())
      return EqObjPtr(shared_from_this());

   y.push_back(shared_from_this());
   return EqObjPtr(new Add(y));
}

bool Variable::isZero()
{
   return false;
}

bool Variable::isOne()
{
   return false;
}

EqObjPtr Variable::clone()
{
    EquationObject *n = new Variable(value);
    return EqObjPtr(n);
}

EqObjPtr Variable::subst(const std::string &str, EqObjPtr eqo)
{
    if (str == this->stringValue())
        return eqo;
    else
        return shared_from_this();
}

EqObjPtr Variable::expand()
{
    return shared_from_this();
}

EqObjPtr Constant::getScale()
{
   return shared_from_this();
}
}
