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

#ifndef MC_CONTEXT_HH
#define MC_CONTEXT_HH
#include <map>
#include <string>
#include "dsmemory.hh"
#include "import.hh"

namespace Eqo
{
class EquationObject;
typedef std::tr1::shared_ptr<EquationObject> EqObjPtr;
}

typedef std::map<std::string, Eqo::EqObjPtr > ModelMap_t;
typedef bool (*inModelListCallback_ptr)(const std::string &);

//// Be able to store rules in the future.
class ContextData {
  public:
    ContextData() : callback_func_ptr_(NULL)
    {
    }

    ModelMap_t model_list_;

    inModelListCallback_ptr callback_func_ptr_;
  private:
//    ContextData();
//    ~ContextData();
    ContextData(const ContextData &);
    const ContextData &operator=(const ContextData &);
};

class DLL_PUBLIC Context {
  public:
    static Context &GetInstance();

    Eqo::EqObjPtr FindInModelList(const std::string &);
    bool          IsInModelList(const std::string &);
    void          SetModelListCallBack(inModelListCallback_ptr);
    ModelMap_t  &GetModelMap();

    void          DeclareModel(const std::string &);
    void          DefineModel(const std::string &, Eqo::EqObjPtr);
    
  private:
    Context();
    ~Context();
    Context(const Context &);
    const Context &operator=(const Context &);

    ContextData context_data_;

    static Context *instance_;
};
#endif

