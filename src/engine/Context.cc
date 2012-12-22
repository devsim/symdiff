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
#include "Context.hh"

Context *Context::instance_;

Context::Context()
{
}

ModelMap_t &Context::GetModelMap()
{
  return context_data_.model_list_;
}

Context &Context::GetInstance()
{
  //// Not thread safe
  if (!instance_)
  {
    instance_ = new Context();
  }
  return *instance_;
}


void Context::SetModelListCallBack(inModelListCallback_ptr foo)
{
    context_data_.callback_func_ptr_ = foo;
}

/*
   Returns true if the model by the given name is in the ModelList
 */
bool Context::IsInModelList(const std::string &str)
{
   ModelMap_t::iterator it, end=context_data_.model_list_.end();
   for (it=context_data_.model_list_.begin(); it != end; ++it)
   {
      if ((*it).first == str)
         return true;
   }
   return false;
}

/*
   If it is in the model list, this will return a pointer to the model with the given
   name.
 */
Eqo::EqObjPtr Context::FindInModelList(const std::string &str)
{
  Eqo::EqObjPtr ret;
  ModelMap_t::iterator it = context_data_.model_list_.find(str);
  if (it != context_data_.model_list_.end())
  {
    ret = it->second;
  }

   return ret;
}

void Context::DeclareModel(const std::string &s)
{
  if (!FindInModelList(s))
  {
//#warning "decide if we should zero out an existing model"
    context_data_.model_list_.insert(std::make_pair(s, Eqo::EqObjPtr()));
  }
}

void Context::DefineModel(const std::string &s, Eqo::EqObjPtr e)
{
  GetModelMap()[s] = e;
}

