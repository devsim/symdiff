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
#include "EquationFunctions.hh"
#include "EquationObject.hh"
#include "mcModelCompiler.hh"
#include "parseexpr.hh"
#include "Context.hh"

#include <sstream>
namespace dsHelper {


/**
 * This is awful, but we need this to prototype
 */
/** here we assume that node models can only reference local models */
bool inModelList(const std::string &x)
{

  Context &context = Context::GetInstance();
  bool inlist = context.IsInModelList(x);
  return inlist;
}

#if 0
bool alwaysInModelList(const std::string &)
{
  return true;
}
#endif

#if 0
bool neverInModelList(const std::string &)
{
  return false;
}
#endif



ret_pair SymdiffEval(const std::string &expr)
{
  bool ret = false;
  std::string retstring;

  EvalExpr::error_t terrors;

  Context &context = Context::GetInstance();
  context.SetModelListCallBack(inModelList);

  Eqo::EqObjPtr testeq = EvalExpr::evaluateExpression(expr, terrors);

  if (!terrors.empty())
  {
    std::ostringstream os;
    os << "While evaluating expression \"" << expr << "\"\n";
    for (EvalExpr::error_t::iterator it = terrors.begin(); it != terrors.end(); ++it)
    {
      os << *it << "\n";
    }
    ret = false;
    retstring = os.str();
  }
  else
  {
    retstring = testeq->stringValue();
    ret = true;
  }

  return std::make_pair(ret, retstring);
}

}

