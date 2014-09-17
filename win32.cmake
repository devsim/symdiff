# Any copyright is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/
#SET(PYTHON_BIN="/usr/bin/python")

IF (${CMAKE_SIZEOF_VOID_P} MATCHES 4)
#32 bit build
SET(TCL_INCLUDE "c:/Tcl/include")
SET(TCL_ARCHIVE "c:/Tcl/lib/tclstub85.lib")
SET(TCL_BIN     "c:/Tcl/bin/tclsh.exe")
SET(PYTHON_INCLUDE "c:/Python27/include")
SET(PYTHON_ARCHIVE "c:/Python27/libs/python27.lib")
ELSE (${CMAKE_SIZEOF_VOID_P} MATCHES 4)
#64 bit build
SET(TCL_INCLUDE "c:/Tcl_win64/include")
SET(TCL_ARCHIVE "c:/Tcl_win64/lib/tclstub85.lib")
SET(TCL_BIN     "c:/Tcl_win64/bin/tclsh.exe")
SET(PYTHON_INCLUDE "c:/Python27_win64/include")
SET(PYTHON_ARCHIVE "c:/Python27_win64/libs/python27.lib")
ENDIF (${CMAKE_SIZEOF_VOID_P} MATCHES 4)

SET (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")
SET (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SAFESEH:NO")
SET (CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /SAFESEH:NO")
