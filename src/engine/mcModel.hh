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

#ifndef MC_MODEL_HH
#define MC_MODEL_HH
#include "EquationObject.hh"
namespace Eqo {
class Model : public EquationObject {
    public:

        Model(std::string);
        ~Model() {};
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
          return std::vector<EqObjPtr>();
        }

        bool hasReciprocal() {return false;}
        EqObjPtr getReciprocal();

        std::set<std::string> getReferencedType(Eqo::EqObjType rt) {
            return CreateSetIfThisType(rt);
        }

        std::string getName() const
        {
          return value;
        }

    private:
        std::string createStringValue() const;

        Model(const Model &);
        Model operator=(const Model &);

        //Models are stored elsewhere
        const std::string value;
};

inline EqObjPtr mod(const std::string &x)
{
   return EqObjPtr(new Model(std::string(x)));
}
}
#endif
