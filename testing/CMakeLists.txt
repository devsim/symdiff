INCLUDE_DIRECTORIES (
)

# pass linker so order important

IF (WIN32)
SET (DIFF C:/cygwin/bin/diff.exe)
SET (PERL C:/cygwin/bin/perl.exe)
SET (RUNDIFFTEST ${PERL} ${PROJECT_SOURCE_DIR}/testing/rundifftest.pl)
SET (GOLDENDIR   ${PROJECT_SOURCE_DIR}/goldenresults/win32)
SET (RUNDIR      ${PROJECT_SOURCE_DIR}/testing)
SET (OUTPUTDIR   ${PROJECT_BINARY_DIR}/testing)
SET (TCLCOMP     ${PROJECT_BINARY_DIR}/src/tclcomp/Release/symdiff_tcl)
SET (PYTHONCOMP   ${PROJECT_BINARY_DIR}/src/tclcomp/Release/symdiff)
ELSE (WIN32)
SET (DIFF diff)
SET (RUNDIFFTEST ${PROJECT_SOURCE_DIR}/testing/rundifftest.pl)
SET (GOLDENDIR   ${PROJECT_SOURCE_DIR}/goldenresults/unix)
SET (RUNDIR      ${PROJECT_SOURCE_DIR}/testing)
SET (OUTPUTDIR   ${PROJECT_BINARY_DIR}/testing)
SET (TCLCOMP   ${PROJECT_BIN_DIR}/symdiff_tcl)
SET (PYTHONCOMP   ${PROJECT_BIN_DIR}/symdiff)
ENDIF (WIN32)

ENABLE_TESTING()

SET (TCLTESTS symdiff1 symdiff2 symdiff3 symdiff4 arrhenius_tcl units)
FOREACH(I ${TCLTESTS})
ADD_TEST("${I}" ${RUNDIFFTEST} "${TCLCOMP} < ${RUNDIR}/${I}.tcl" ${GOLDENDIR} ${I}.out ${RUNDIR} ${OUTPUTDIR})
ENDFOREACH(I)

SET (EXAMPLES_DIR ${PROJECT_SOURCE_DIR}/examples)
SET (PYTHONTESTS arrhenius modellist1 ordered remove1 subexpression1 undefined1 utf8)
FOREACH(I ${PYTHONTESTS})
ADD_TEST("${I}_py" ${RUNDIFFTEST} "${PYTHONCOMP} < ${EXAMPLES_DIR}/${I}.py" ${GOLDENDIR} ${I}_py.out ${EXAMPLES_DIR} ${OUTPUTDIR})
ENDFOREACH(I)

