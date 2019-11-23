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

#include "Utility.hh"
#include "EquationObject.hh"

#include <algorithm>
#include <functional>

namespace Eqo {
namespace {
//// order by CONST_OBJ, the VARIABLE_OBJ, then everything else see enum
struct EqVecCompare : public std::binary_function<EqObjPtr, EqObjPtr, bool>
{
  bool operator()(EqObjPtr x, EqObjPtr y)
  {
    const EqObjType xtype = x->getType();
    const EqObjType ytype = y->getType();

    bool ret = false;

    if (xtype < ytype)
    {
      ret = true;
    }
    else if (xtype == ytype)
    {
      const std::string &xstr = x->stringValue();
      const std::string &ystr = y->stringValue();

      ret = (xstr < ystr);
    }

    return ret;
  }
};

}
/// Sorts in order of constants, variables, then other objects
void SortEqVector(std::vector<EqObjPtr> &v1)
{
  std::sort(v1.begin(), v1.end(), EqVecCompare());
}

}

