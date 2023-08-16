/***
Copyright 2012 DEVSIM LLC

SPDX-License-Identifier: Apache-2.0
***/

#ifndef EQUATION_FUNCTIONS_HH
#define EQUATION_FUNCTIONS_HH
#include <memory>
#include "SymdiffImport.hh"
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
DLL_PROTECTED ret_pair SymdiffEval(const std::string &);
}

#endif
