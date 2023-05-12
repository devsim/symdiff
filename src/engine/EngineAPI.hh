/***
Copyright 2012 DEVSIM LLC

SPDX-License-Identifier: Apache-2.0
***/

#ifndef ENGINEAPI_HH
#define ENGINEAPI_HH
#include <memory>
#include "import.hh"
#include <string>
#include <vector>
#include <set>
namespace Eqo {
class EquationObject;
typedef std::shared_ptr<EquationObject> EqObjPtr;
}

namespace EngineAPI {
enum EqObjType {CONST_OBJ=0, VARIABLE_OBJ, ADD_OBJ, PRODUCT_OBJ, EXPONENT_OBJ, POW_OBJ, LOG_OBJ, MODEL_OBJ, USERFUNC_OBJ, BLOGICAL_OBJ, ULOGICAL_OBJ, IF_OBJ, IFELSE_OBJ, NUM_TYPES};

typedef Eqo::EqObjPtr (*EqUnaryFuncPtr) (Eqo::EqObjPtr);
typedef Eqo::EqObjPtr (*EqBinaryFuncPtr) (Eqo::EqObjPtr, Eqo::EqObjPtr);

Eqo::EqObjPtr DLL_PUBLIC createUnaryLogical(const std::string &/*unaryOp*/, Eqo::EqObjPtr /*arg*/);
Eqo::EqObjPtr DLL_PUBLIC createBinaryLogical(const std::string &/*unaryOp*/, Eqo::EqObjPtr /*arg*/, Eqo::EqObjPtr /*arg*/);
Eqo::EqObjPtr DLL_PUBLIC createIfObj(Eqo::EqObjPtr /*test*/, Eqo::EqObjPtr /*result*/);
Eqo::EqObjPtr DLL_PUBLIC createIfElseObj(Eqo::EqObjPtr /*test*/, Eqo::EqObjPtr /*left*/, Eqo::EqObjPtr /*right*/);
/// Non member functions for intuitive math operations
Eqo::EqObjPtr DLL_PUBLIC operator* (Eqo::EqObjPtr x, Eqo::EqObjPtr y);
Eqo::EqObjPtr DLL_PUBLIC pow (Eqo::EqObjPtr x, Eqo::EqObjPtr y);
Eqo::EqObjPtr DLL_PUBLIC operator/ (Eqo::EqObjPtr x, Eqo::EqObjPtr y);
Eqo::EqObjPtr DLL_PUBLIC operator+ (Eqo::EqObjPtr x, Eqo::EqObjPtr y);
Eqo::EqObjPtr DLL_PUBLIC operator- (Eqo::EqObjPtr x, Eqo::EqObjPtr y);

Eqo::EqObjPtr DLL_PUBLIC exp (Eqo::EqObjPtr x);

Eqo::EqObjPtr DLL_PUBLIC pow (Eqo::EqObjPtr x, Eqo::EqObjPtr y);

Eqo::EqObjPtr DLL_PUBLIC log (Eqo::EqObjPtr x);

Eqo::EqObjPtr DLL_PUBLIC diff(Eqo::EqObjPtr x, Eqo::EqObjPtr y);

Eqo::EqObjPtr DLL_PUBLIC con(double x);

Eqo::EqObjPtr DLL_PUBLIC mod(const char *x);

Eqo::EqObjPtr DLL_PUBLIC mod(const std::string &x);

Eqo::EqObjPtr DLL_PUBLIC var(const char *x);

Eqo::EqObjPtr DLL_PUBLIC var(const std::string &x);

Eqo::EqObjPtr DLL_PUBLIC sqrt(Eqo::EqObjPtr x);

Eqo::EqObjPtr DLL_PUBLIC reciprocal_sqrt(Eqo::EqObjPtr x);

/// how we print things
std::ostream & operator<< (std::ostream &os, Eqo::EqObjPtr foo);

/// keeps simplifying expression until string value doesn't change
Eqo::EqObjPtr DLL_PUBLIC Simplify(Eqo::EqObjPtr x);

Eqo::EqObjPtr DLL_PUBLIC getConstantFactor(Eqo::EqObjPtr x);

Eqo::EqObjPtr DLL_PUBLIC Expand(Eqo::EqObjPtr x);

Eqo::EqObjPtr DLL_PUBLIC getUnscaledValue(Eqo::EqObjPtr x);

Eqo::EqObjPtr DLL_PUBLIC getUnsignedValue(Eqo::EqObjPtr x);

Eqo::EqObjPtr DLL_PUBLIC getSign(Eqo::EqObjPtr x);

/// Sorts in order of constants, variables, then other objects
void SortEqVector(std::vector<Eqo::EqObjPtr> &v1);

Eqo::EqObjPtr DLL_PUBLIC subst(Eqo::EqObjPtr a, Eqo::EqObjPtr b, Eqo::EqObjPtr c);

Eqo::EqObjPtr DLL_PUBLIC getNegation(Eqo::EqObjPtr x);

bool DLL_PUBLIC isBinaryFunction(const std::string &str);
bool DLL_PUBLIC isUnaryFunction(const std::string &str);

EqBinaryFuncPtr DLL_PUBLIC getBinaryFuncPtr(const std::string &);
EqUnaryFuncPtr DLL_PUBLIC getUnaryFuncPtr(const std::string &);

std::string DLL_PUBLIC getName(Eqo::EqObjPtr x);
std::string DLL_PUBLIC getType(Eqo::EqObjPtr x);
std::set<std::string> DLL_PUBLIC getReferencedType(Eqo::EqObjPtr x, EqObjType t);
double DLL_PUBLIC getDoubleValue(Eqo::EqObjPtr x);
std::string DLL_PUBLIC getStringValue(Eqo::EqObjPtr x);
EqObjType DLL_PUBLIC getEnumeratedType(Eqo::EqObjPtr x);
std::vector<Eqo::EqObjPtr> DLL_PUBLIC getArgs(Eqo::EqObjPtr x);

typedef bool (*inModelListCallback_ptr)(const std::string &);
void DLL_PUBLIC SetModelListCallBack(inModelListCallback_ptr);

typedef Eqo::EqObjPtr (*modelDerivativeRule_ptr)(Eqo::EqObjPtr, Eqo::EqObjPtr);
void DLL_PUBLIC SetDerivativeRule(modelDerivativeRule_ptr);
}
#endif
