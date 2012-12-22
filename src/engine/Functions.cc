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

#include "Functions.hh"

namespace Eqo
{
UnaryTblEntry UnaryTable[] = {
    {"simplify",    Simplify,         "simplify(obj)         -- Simplify as much as possible"},
    {"exp",         exp,              "exp(obj)              -- Exponentiation with respect to e"},
    {"expand",        Expand,          "expand(obj)          -- Perform expansion of products with sums"},
    {"log",         log,              "log(obj)              -- Natural logarithm"},
    {"unscaledval", getUnscaledValue, "unscaledval(obj)      -- Get value without constant scaling"},
    {"scale",       getConstantFactor,"scale(obj)            -- Get constant factor"},
    {"unsignedval", getUnsignedValue, "unsignedval(obj)      -- Get unsigned value"},
    {"sign",        getSign,          "sign(obj)             -- Get sign as 1 or -1"},
    {NULL, NULL, NULL}
};

BinaryTblEntry BinaryTable[] = {
    {"pow",  pow,  "pow(obj1, obj2)       -- Raise obj1 to the power of obj2"},
    {"diff", diff, "diff(obj1, obj2)      -- Take derivative  of obj1 with respect to obj2"},
    {NULL, NULL, NULL}
};

EqUnaryFuncPtr getUnaryFuncPtr(std::string x) {
    size_t i=0; 
    while (UnaryTable[i].name != NULL)
    {
        if (x == UnaryTable[i].name)
            return UnaryTable[i].func;
        ++i;
    }
    return NULL;
}

EqBinaryFuncPtr getBinaryFuncPtr(std::string x) {
    size_t i=0; 
    while (BinaryTable[i].name != NULL)
    {
        if (x == BinaryTable[i].name)
            return BinaryTable[i].func;
        ++i;
    }
    return NULL;
}
}

