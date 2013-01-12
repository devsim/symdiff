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

#ifndef PRODUCT_HH
#define PRODUCT_HH
#include "EquationObject.hh"
namespace Eqo {
class Product : public EquationObject {
    public:
        friend class Pow;
        Product(EqObjPtr, EqObjPtr);
        Product(std::vector<EqObjPtr>);

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

        void ProductVecSimplify(std::vector<EqObjPtr> &);

        bool hasReciprocal() {return false;}
        EqObjPtr getReciprocal() {assert(false); return con(0);}

        std::set<std::string> getReferencedType(Eqo::EqObjType rt)
        {
            return UniteReferencedType(rt, values);
        }

        std::vector<EqObjPtr> getArgs() {
          return createArgs(values);
        }

        std::string getName() const
        {
          return "*";
        }

    private:
        std::string createStringValue() const;

        Product(const Product &);
        Product operator=(const Product &);

        std::vector<EqObjPtr> values;
};
}
#endif
