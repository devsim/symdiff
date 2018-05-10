# Any copyright is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/
#SET(PYTHON_BIN="/usr/bin/python")

#64 bit build
#SET(TCL_INCLUDE "c:/Tcl/include")
#SET(TCL_ARCHIVE "c:/Tcl/lib/tclstub85.lib")
SET(TCL_INCLUDE "c:/Miniconda-x64/Library/include")
SET(TCL_ARCHIVE "c:/Miniconda-x64/Library/lib/tcl86t.lib")
SET(TCL_BIN     "c:/Miniconda-x64/Library/bin/tclsh.exe")
SET (PYTHON_ARCHIVE C:/Miniconda-x64/libs/python27.lib)
SET (PYTHON_INCLUDE C:/Miniconda-x64/include)

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fp:strict /EHsc")
SET (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")
SET (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SAFESEH:NO")
SET (CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /SAFESEH:NO")
