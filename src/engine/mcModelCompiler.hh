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

#ifndef MC_MODEL_COMPILER_HH
#define MC_MODEL_COMPILER_HH
#include "EquationObject.hh"
#include <string>
Eqo::EqObjPtr ClearModel(const std::string &);

Eqo::EqObjPtr DeclareModel(const std::string &);

Eqo::EqObjPtr GetModelValue(const std::string &);

Eqo::EqObjPtr DefineModel(const std::string &, Eqo::EqObjPtr);
#endif

