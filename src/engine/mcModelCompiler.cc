/***
Copyright 2012 DEVSIM LLC

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

#include "mcModelCompiler.hh"
#include "Functions.hh"

#include <map>
#include <list>
#include <string>
#include <utility>

#include "mcModel.hh"
#include "Context.hh"

Eqo::EqObjPtr ClearModel(const std::string &s)
{
  Context &context = Context::GetInstance();
  context.ClearModel(s);
  return Eqo::con(0.0);
}

Eqo::EqObjPtr DeclareModel(const std::string &s)
{
  Context &context = Context::GetInstance();
  context.DeclareModel(s);
  return Eqo::mod(s);
}

Eqo::EqObjPtr DefineModel(const std::string &s, Eqo::EqObjPtr e)
{
  Context &context = Context::GetInstance();
  context.DefineModel(s, e);
  return Eqo::mod(s);
}

/// Does not error out.  For this use top level command
Eqo::EqObjPtr GetModelValue(const std::string &s)
{
  Eqo::EqObjPtr ret = Eqo::var("UNDEFINED");

  Context &context = Context::GetInstance();
  if (context.IsInModelList(s))
  {
    Eqo::EqObjPtr x = context.FindInModelList(s);
    if (x)
    {
      ret = x;
    }
  }

  return ret;
}

