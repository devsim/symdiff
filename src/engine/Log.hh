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

#ifndef LOG_HH
#define LOG_HH
#include "EquationObject.hh"
namespace Eqo {
class Log : public EquationObject {
    public:
        Log(EqObjPtr);

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

        bool hasReciprocal() {return false;}
        EqObjPtr getReciprocal() {assert(false); return con(0);}
        std::set<std::string> getReferencedType(Eqo::EqObjType rt)
        {
            return value->getReferencedType(rt);
        }

        friend class Exponent;

        std::vector<EqObjPtr> getArgs() {
          return createArgs(value);
        }

        std::string getName() const
        {
          return "log";
        }

    private:
        std::string createStringValue() const;

        Log(const Log &);
        Log operator=(const Log &);

        const EqObjPtr value;
};
}
#endif

