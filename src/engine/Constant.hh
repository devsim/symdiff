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

#ifndef CONSTANT_HH
#define CONSTANT_HH
#include "EquationObject.hh"
namespace Eqo {
class Constant : public EquationObject {
    public:
        Constant(double);
        ~Constant() {};


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

        bool hasReciprocal()
        {
          return !(this->isZero());
        }

        EqObjPtr getReciprocal();

        double getDoubleValue()
        {
          return dvalue;
        }

        std::set<std::string> getReferencedType(Eqo::EqObjType rt) {
            return CreateSetIfThisType(rt);
        }

        friend class Pow;
        friend class Product;

        std::vector<EqObjPtr> getArgs() {
          return std::vector<EqObjPtr>();
        }

        std::string getName() const
        {
          return EquationObject::stringValue();
        }
    private:
        std::string createStringValue() const;

        Constant(const Constant &);
        Constant operator=(const Constant &);

        const double dvalue;
};
}
#endif

