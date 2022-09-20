/***
Copyright 2012 DEVSIM LLC

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

#ifndef IF_ELSE_HH
#define IF_ELSE_HH
#include "EquationObject.hh"

namespace Eqo {
class IfObj : public EquationObject
{
    public:
        IfObj(EqObjPtr /*test*/, EqObjPtr /*result*/);
        ~IfObj() {};

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

        std::vector<EqObjPtr> getArgs() {
          return createArgs(test, arg);
        }

        bool hasReciprocal() {return false;}
        EqObjPtr getReciprocal();

        std::set<std::string> getReferencedType(Eqo::EqObjType rt);

        std::string getName() const
        {
          return "if";
        }

    private:
        std::string createStringValue() const;

        IfObj(const IfObj &);
        IfObj operator=(const IfObj &);

        const EqObjPtr test;
        const EqObjPtr arg;
};

class IfElseObj : public EquationObject
{
    public:
        IfElseObj(EqObjPtr /*test*/, EqObjPtr /*left*/, EqObjPtr /*right*/);
        ~IfElseObj() {};

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

        std::vector<EqObjPtr> getArgs() {
          return createArgs(test, arg1, arg2);
        }

        bool hasReciprocal() {return false;}
        EqObjPtr getReciprocal();

        std::set<std::string> getReferencedType(Eqo::EqObjType rt);

        std::string getName() const
        {
          return "ifelse";
        }
    private:
        std::string createStringValue() const;

        IfElseObj(const IfElseObj &);
        IfElseObj operator=(const IfElseObj &);

        EqObjPtr test;
        EqObjPtr arg1;
        EqObjPtr arg2;
};
}

#endif
