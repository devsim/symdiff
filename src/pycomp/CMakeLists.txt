
INCLUDE_DIRECTORIES (
  ../engine
)

SET (PYTHON_SRCS
  PythonSymdiffCommands.cc
)

#SET(PYVERSION symdiff_py2)

FUNCTION(build_python_version target_name module_name is_python3t)
ADD_LIBRARY (${target_name} SHARED ${PYTHON_SRCS})
TARGET_LINK_LIBRARIES (${target_name} symdiff_dynamic)
IF(WIN32)
  SET (module_suffix ".pyd")
  IF (${is_python3t})
    SET (module_name "${module_name}_abi3t")
  ELSE ()
    SET (module_name "${module_name}_abi3")
  ENDIF ()
ELSE()
  IF (${is_python3t})
    SET (module_suffix ".abi3t.so")
  ELSE ()
    SET (module_suffix ".abi3.so")
  ENDIF ()
ENDIF()
SET_TARGET_PROPERTIES(${target_name} PROPERTIES PREFIX "" SUFFIX "${module_suffix}" OUTPUT_NAME "${module_name}")

ADD_CUSTOM_COMMAND(TARGET ${target_name}
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_LIBRARY_DIR}/symdiff
          COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${target_name}> ${PROJECT_LIBRARY_DIR}/symdiff
)

IF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
SET_TARGET_PROPERTIES(${target_name} PROPERTIES INSTALL_RPATH "\$ORIGIN/")
ENDIF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
IF (APPLE)
SET_TARGET_PROPERTIES(${target_name} PROPERTIES LINK_FLAGS "-undefined dynamic_lookup -flat_namespace")
ENDIF (APPLE)
ENDFUNCTION(build_python_version)

IF (PYTHON3)
build_python_version(symdiff_py3 symdiff_py3 FALSE)
TARGET_INCLUDE_DIRECTORIES (symdiff_py3 PUBLIC ${PYTHON3_INCLUDE})
IF(WIN32)
TARGET_LINK_LIBRARIES (symdiff_py3 ${PYTHON3_ARCHIVE})
ELSE(WIN32)
# macOS and Linux do not need to dynamically link against python
ENDIF(WIN32)
target_compile_definitions(symdiff_py3 PRIVATE -DPy_LIMITED_API=0x03090000)
ENDIF (PYTHON3)

IF (PYTHON3T)
build_python_version(symdiff_py3t symdiff_py3 TRUE)
TARGET_INCLUDE_DIRECTORIES (symdiff_py3t PUBLIC ${PYTHON3T_INCLUDE})
target_compile_definitions(symdiff_py3t PRIVATE SYMDIFF_PYTHON3T Py_TARGET_ABI3T=0x30f0000)
IF(WIN32)
target_compile_definitions(symdiff_py3t PRIVATE SYMDIFF_PYTHON3T Py_GIL_DISABLED=1)
TARGET_LINK_LIBRARIES (symdiff_py3t ${PYTHON3T_ARCHIVE})
ENDIF(WIN32)
ENDIF (PYTHON3T)

