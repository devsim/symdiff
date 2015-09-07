# Any copyright is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/
#SET(PYTHON_BIN="/usr/bin/python")

IF (${CMAKE_SIZEOF_VOID_P} MATCHES 4)
#32 bit build
SET(TCL_INCLUDE "c:/Tcl/include")
SET(TCL_ARCHIVE "c:/Tcl/lib/tclstub85.lib")
SET(TCL_BIN     "c:/Tcl/bin/tclsh.exe")
SET(PYTHON_INCLUDE "c:/Anaconda/include")
SET(PYTHON_ARCHIVE "c:/Anaconda/libs/python27.lib")
ELSE (${CMAKE_SIZEOF_VOID_P} MATCHES 4)
#64 bit build
SET(TCL_INCLUDE "c:/Tcl/include")
SET(TCL_ARCHIVE "c:/Tcl/lib/tclstub85.lib")
SET(TCL_BIN     "c:/Tcl/bin/tclsh.exe")
SET (PYTHON_ARCHIVE C:/Anaconda/libs/python27.lib)
SET (PYTHON_INCLUDE C:/Anaconda/include)
ENDIF (${CMAKE_SIZEOF_VOID_P} MATCHES 4)

SET (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")
SET (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SAFESEH:NO")
SET (CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /SAFESEH:NO")
