INCLUDE_DIRECTORIES (
)

SET (MC_SRCS
    ${CMAKE_CURRENT_BINARY_DIR}/mcParser.cc
    ${CMAKE_CURRENT_BINARY_DIR}/mcScanner.cc
    mcModelCompiler.cc
    mcTest.cc
    EquationFunctions.cc
    parseexpr.cc
    Context.cc
    SubExpr.cc
    ProcessModelOrder.cc
    mcModel.cc
)

SET (CXX_SRCS
    EngineAPI.cc
    EquationObject.cc
    UserFunc.cc
    LogicalFunc.cc
    Add.cc
    Constant.cc
    EquationObject.cc
    Exponent.cc
    IfElse.cc
    Log.cc
    Pow.cc
    Product.cc
    Variable.cc
    Functions.cc
    Utility.cc
)

INCLUDE_DIRECTORIES (
    ${CMAKE_CURRENT_SOURCE_DIR}
)

ADD_LIBRARY(symdiff SHARED ${CXX_SRCS} ${MC_SRCS})


IF (WIN32)
SET_SOURCE_FILES_PROPERTIES(mcScanner.cc mcParser.cc PROPERTIES GENERATED TRUE)
ELSE (WIN32)
SET_SOURCE_FILES_PROPERTIES(mcScanner.cc mcParser.cc PROPERTIES GENERATED TRUE COMPILE_FLAGS "-Wno-unused-function -Wno-sign-compare")
ENDIF (WIN32)

ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mcScanner.cc
    COMMAND ${FLEX}
    ARGS    -Pmc -omcScanner.cc ${CMAKE_CURRENT_SOURCE_DIR}/mcScanner.l
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/mcParser.hh ${CMAKE_CURRENT_SOURCE_DIR}/mcScanner.l
		    mcTest.hh EquationObject.hh UserFunc.hh
)

ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mcParser.cc ${CMAKE_CURRENT_BINARY_DIR}/mcParser.hh
    COMMAND ${BISON}
    ARGS -pmc --debug -v -d -o mcParser.cc ${CMAKE_CURRENT_SOURCE_DIR}/mcParser.y
    # these must be read from parser.y
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/mcParser.y EquationObject.hh UserFunc.hh mcTest.hh mcModelCompiler.hh mcModel.hh
)

GET_TARGET_PROPERTY(SYMDIFF_NAME symdiff LOCATION)
ADD_CUSTOM_COMMAND(TARGET symdiff
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_LIBRARY_DIR}
          COMMAND ${CMAKE_COMMAND} -E copy ${SYMDIFF_NAME} ${PROJECT_LIBRARY_DIR}/.
)
IF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
SET_TARGET_PROPERTIES(symdiff PROPERTIES INSTALL_RPATH "\$ORIGIN/")
ENDIF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
#IF (APPLE)
#SET_TARGET_PROPERTIES(symdiff PROPERTIES INSTALL_RPATH "@loader_path/")
#ENDIF (APPLE)


