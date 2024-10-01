/***
Copyright 2024 DEVSIM LLC

SPDX-License-Identifier: Apache-2.0
***/

#ifndef SYMDIFFAPI_H
#define SYMDIFFAPI_H
#include "SymdiffImport.hh"

/** this releases the reference count on the object if not needed */
/** this does not need to be extern "C" if handled from a C++ based implementation */
extern "C" DLL_PUBLIC void SYMDIFFobj_free(void *);

extern "C" DLL_PUBLIC bool SYMDIFF_get_status(void *);

extern "C" DLL_PUBLIC const char * SYMDIFF_get_string(void *);

extern "C" DLL_PUBLIC const char * SYMDIFF_get_error(void *);

extern "C" DLL_PUBLIC void * SYMDIFF_parse(const char *);

/**
extern "C" DLL_PUBLIC void * SYMDIFF_apply_func(const char *func, void **args, numargs);
extern "C" DLL_PUBLIC void * SYMDIFF_clone(void *);
extern "C" DLL_PUBLIC void * SYMDIFF_simplify(void *);
extern "C" DLL_PUBLIC void * SYMDIFF_model(const char *);
extern "C" DLL_PUBLIC void * SYMDIFF_var(const char *);
*/

#endif

