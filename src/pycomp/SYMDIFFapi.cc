/***
Copyright 2024 DEVSIM LLC

SPDX-License-Identifier: Apache-2.0
***/

#include "SYMDIFFapi.hh"
#include "EngineAPI.hh"
#include "EquationFunc.hh"

#include <string>

struct SYMDIFFobj {
    Eqo::EqObjPtr eqobj_;
    std::string string_value;
    std::string error_string;
    bool status = false;
};

extern "C" DLL_PUBLIC void SYMDIFFobj_free(void *x)
{
    auto y = reinterpret_cast<SYMDIFFobj *>(x);
    delete y;
}

extern "C" DLL_PUBLIC bool SYMDIFF_get_status(void *x)
{
    auto y = reinterpret_cast<SYMDIFFobj *>(x);
    return y->status;
}

extern "C" DLL_PUBLIC const char * SYMDIFF_get_string(void *x)
{
    auto y = reinterpret_cast<SYMDIFFobj *>(x);
    return y->string_value.data();
}

extern "C" DLL_PUBLIC const char * SYMDIFF_get_error(void *x)
{
    auto y = reinterpret_cast<SYMDIFFobj *>(x);
    return y->error_string.data();
}

extern "C" DLL_PUBLIC void * SYMDIFF_parse(const char *input_string)
{
    auto rv = new SYMDIFFobj;
    auto ep = sdHelp::SymdiffEval(input_string);
    if (ep.first)
    {
        rv->status = ep.first;
        rv->string_value = ep.second.string_;
        rv->eqobj_ = ep.second.eqptr_;
    }
    else
    {
        rv->error_string = ep.second.string_;
    }
    return rv;
}

