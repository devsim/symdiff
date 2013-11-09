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

#ifndef SUBEXPR_HH
#define SUBEXPR_HH
#include <memory>
#include "import.hh"

#include <string>
#include <map>
#include <vector>



namespace Eqo
{
class EquationObject;
typedef std::shared_ptr<EquationObject> EqObjPtr;
}

typedef std::vector<std::string> ModelNameVector_t;
typedef std::map<std::string, Eqo::EqObjPtr > ModelMap_t;


class SubExpr;

class SubExprData
{
  public:
    SubExprData() : refcount(0) {}
    explicit SubExprData(Eqo::EqObjPtr x);

    void addCount()
    {
      ++refcount;
    }
    size_t getCount() const
    {
      return refcount;
    }

    Eqo::EqObjPtr getEquation() const;

    const std::string &getName(SubExpr &subexpr) const;

  private:
    size_t refcount;
    Eqo::EqObjPtr equation;
    mutable std::string name;
};

/// Creates sub expressions on the fly
class DLL_PUBLIC SubExpr
{
  public:
    SubExpr();

    std::string GetUniqueName();

    const std::string &GetErrorString() const
    {
      return errorString_;
    }

    void CreateSubexpressions(ModelMap_t &);
    void RemoveZeros(ModelMap_t &);

  private:
    bool removeZeros(ModelMap_t &);
    void scanSubexpression(Eqo::EqObjPtr &);
    void createSubexpressions(ModelMap_t &);

    enum ProcessStatus_t {UNTOUCHED = 0, PROCESSING, DONE};

    /// Use this for detecting cycles
    std::map<std::string, ProcessStatus_t> processStatusMap_;

    /// report errors if there is a problem
    std::string errorString_;

    std::map<std::string, SubExprData> SubExprMap;
    std::vector<std::string>       SubExprOrdered;

    size_t unique_counter_;
};


#endif

