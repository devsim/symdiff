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

#ifndef EQUATION_FUNCTIONS_HH
#define EQUATION_FUNCTIONS_HH
#include <memory>
#include "import.hh"
#include <string>
#include <utility>

namespace Eqo {
class EquationObject;
typedef std::shared_ptr<EquationObject> EqObjPtr;
}

namespace dsHelper {
struct ret_data {
  std::string   string_;
  Eqo::EqObjPtr eqptr_;
};

typedef std::pair<bool, ret_data> ret_pair;
DLL_PUBLIC ret_pair SymdiffEval(const std::string &);
}

#endif
