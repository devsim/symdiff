# Any copyright is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/
#SET(PYTHON_BIN="/usr/bin/python")

ADD_DEFINITIONS(-DTCL_THREADS -DUSE_TCL_STUBS)
ADD_DEFINITIONS(-DSTATIC_BUILD -D_USE_MATH_DEFINES)
SET (CMAKE_CXX_WARNING_LEVEL 4)


# warning C4251 for dll exports
# warning C4005 concerning macro redefines in stdint.h
# warning C4996: 'isatty': The POSIX name for this item is deprecated
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fp:strict /wd4251 /wd4005 /wd4996")
SET (CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} /fp:strict /wd4251 /wd4005 /wd4996")
#64 bit build
#SET(TCL_INCLUDE "c:/Tcl/include")
#SET(TCL_ARCHIVE "c:/Tcl/lib/tclstub85.lib")
IF (${CMAKE_SIZEOF_VOID_P} MATCHES 4)
SET (MINICONDA2 C:/Miniconda)
SET (MINICONDA3 C:/Miniconda36)
ELSE (${CMAKE_SIZEOF_VOID_P} MATCHES 4)
SET (MINICONDA2 C:/Miniconda-x64)
SET (MINICONDA3 C:/Miniconda36-x64)
ENDIF (${CMAKE_SIZEOF_VOID_P} MATCHES 4)

SET(TCL_INCLUDE "${MINICONDA2}/Library/include")
SET(TCL_ARCHIVE "${MINICONDA2}/Library/lib/tclstub86.lib")
SET(TCL_BIN     "${MINICONDA2}/Library/bin/tclsh.exe")
SET (PYTHON_ARCHIVE ${MINICONDA2}/libs/python27.lib)
SET (PYTHON_INCLUDE ${MINICONDA2}/include)
SET (PYTHON3_ARCHIVE ${MINICONDA3}/libs/python36.lib)
SET (PYTHON3_INCLUDE ${MINICONDA3}/include)

SET (PERL  "C:/cygwin/bin/perl.exe")
SET (FLEX  "C:/cygwin/bin/flex.exe")
SET (BISON "C:/cygwin/bin/bison.exe")
SET (DIFF  "C:/cygwin/bin/diff.exe")

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fp:strict /EHsc")
SET (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")
SET (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SAFESEH:NO /NODEFAULTLIB:python3")
SET (CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /SAFESEH:NO")

