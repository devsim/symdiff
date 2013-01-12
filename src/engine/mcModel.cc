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

#include "mcModel.hh"
#include "mcModelCompiler.hh"
#include "dsAssert.hh"
#include "Functions.hh"
#include "Context.hh"

namespace Eqo {
EqObjPtr Model::getScale()
{
   return con(1.0);
}

EqObjPtr Model::getUnscaledValue()
{
   return shared_from_this();
}

double Model::getSign()
{
    return 1.0;
}

EqObjPtr Model::getUnsignedValue()
{
   return shared_from_this();
}

EqObjPtr Model::expand()
{
   return shared_from_this();
}

EqObjPtr Model::clone()
{
   return mod(value);
}

EqObjPtr Model::subst(const std::string &str, EqObjPtr eqo)
{
    if (str == this->stringValue())
    {
//// TODO: how does this work
      return eqo->clone();
    }
    else
    {
      return shared_from_this();
    }
}

Model::Model(std::string var) : EquationObject(MODEL_OBJ), value(var)
{
}

std::string Model::createStringValue() const
{
    return value;
}

/// Should make it possible to specify derivative
EqObjPtr Model::Derivative(EqObjPtr foo)
{
    Context &context = Context::GetInstance();

    dsAssert(context.IsInModelList(value), "UNEXPECTED");

    if (foo->stringValue() == value)
    {
        return con(1.0);
    }

    EqObjPtr dval;

    if (context.IsInModelList(value))
    {
      EqObjPtr eq = context.FindInModelList(value);
      if (eq)
      {
        dval =  eq->Derivative(foo)->Simplify();
      }
    }

    EqObjPtr ret;

#if 0
    if (dval && dval->isZero())
    {
      ret = con(0.0);
    }
    else
#endif
    {
      std::string bar(value);
      bar += "__"; 
      bar += foo->stringValue();

      if (!context.IsInModelList(bar))
      {
         context.DefineModel(bar, dval);
      }
      else
      {
/// model already defined elsewhere, should we redefine it
         context.DefineModel(bar, dval);
      }
      ret = mod(bar);
    }

    return ret;
}

EqObjPtr Model::Simplify()
{
   return shared_from_this();
}

/**
 * This function may never be called if variables
 * are turned into Pow's.
 */
EqObjPtr Model::CombineProduct(std::vector<EqObjPtr> y)
{
   if (y.empty())
      return shared_from_this();

   y.push_back(shared_from_this());
   return EqObjPtr(new Product(y));
}

EqObjPtr Model::CombineAdd(std::vector<EqObjPtr> y)
{
   if (y.empty())
      return shared_from_this();

   y.push_back(shared_from_this());
   return EqObjPtr(new Add(y));
}

bool Model::isZero()
{
   return false;
}

bool Model::isOne()
{
   return false;
}

}

