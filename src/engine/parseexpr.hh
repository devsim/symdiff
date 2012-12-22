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

#ifndef PARSEEXPR_HH
#define PARSEEXPR_HH
#include "dsmemory.hh"
#include <list>
#include <string>

namespace Eqo {
    class EquationObject;
    typedef std::tr1::shared_ptr<EquationObject> EqObjPtr;
};

namespace EvalExpr {
typedef std::list<std::string> error_t;

/// We are using the parser for a new purpose
void clearVariableMap();

Eqo::EqObjPtr evaluateExpression(const std::string &, error_t &);
}

#endif

