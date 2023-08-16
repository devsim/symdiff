/***
Copyright 2012 DEVSIM LLC

SPDX-License-Identifier: Apache-2.0
***/

#ifndef USER_FUNC_HH
#define USER_FUNC_HH
#include "EquationObject.hh"
#include "SymdiffImport.hh"
#include <string>
#include <vector>
#include <map>
#include <algorithm>
namespace Eqo {
// first arg, simple variable, second arg, is the diff
typedef std::pair<std::string, Eqo::EqObjPtr> UserDiffInfo;
typedef std::vector<UserDiffInfo>             UserDiffInfoVec;

void DLL_PROTECTED SetUserFuncDiffs(std::string, UserDiffInfoVec &);
void DLL_PROTECTED CreateUserFunc(std::string, size_t);

extern std::map<std::string, UserDiffInfoVec> UserFuncMap;

class UserFunc : public EquationObject {
    public:
        UserFunc(std::string, std::vector<EqObjPtr> &);

        std::string getName() const
        {
            return name;
        }

        EqObjPtr Derivative(EqObjPtr);
        EqObjPtr Simplify();

        EqObjPtr CombineProduct(std::vector<EqObjPtr>);
        EqObjPtr CombineAdd(std::vector<EqObjPtr>);

        bool isZero();
        bool isOne();

        EqObjPtr getScale();
        EqObjPtr getUnscaledValue();

        double getSign();
        EqObjPtr getUnsignedValue();

        EqObjPtr clone();
        EqObjPtr subst(const std::string &, EqObjPtr);

        EqObjPtr expand();

        std::vector<EqObjPtr> getArgs()
        {
          return createArgs(args);
        }
        /// Maybe this should be configurable
        bool hasReciprocal() {return false;}
        EqObjPtr getReciprocal();

        std::set<std::string> getReferencedType(Eqo::EqObjType rt);
    private:
        std::string createStringValue() const;

        UserFunc(const UserFunc &);
        UserFunc operator=(const UserFunc &);
        
        std::string              name;  // name of this function (must not be in any other variable table)
        std::vector<EqObjPtr>    args; // number of arguments if initialized this way
};
}
#endif
