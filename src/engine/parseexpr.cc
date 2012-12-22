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

#include "parseexpr.hh"
#include "mcTest.hh"
#include <sstream>
namespace EvalExpr {
static error_t *lerrors;

void clearVariableMap() {
    Eqo::variableMap.clear();
}

/// Returns Equation Object containing the result of calculation, as well as any errors
/// error list should be empty on entry
Eqo::EqObjPtr evaluateExpression(const std::string &x, error_t &errors)
{
    lerrors = &errors;
    YY_BUFFER_STATE yyb = NULL;
//    clearVariableMap();
    yyb = mc_scan_string(x.c_str());
    int retval = 0;
    retval = mcparse();
    if (yyb != NULL)
    {
        mc_delete_buffer(yyb);
    }
    Eqo::EqObjPtr result;
    if (retval == 0)
    {
        result = Eqo::variableMap["$_"];
    }
    else
    {
        result = Eqo::con(0.0);
    }
    lerrors=NULL;
    return result;
}
}

// Not in any namespace
int mcerror(const char *msg) {
    EvalExpr::lerrors->push_back(std::string(msg));
    return 0;
}

