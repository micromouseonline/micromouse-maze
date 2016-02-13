#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/list.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/maze.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/gtest/src/gtest-all.o \
	${TESTDIR}/tests/testCosts.o \
	${TESTDIR}/tests/testDirection.o \
	${TESTDIR}/tests/testList.o \
	${TESTDIR}/tests/testLocation.o \
	${TESTDIR}/tests/testMaze.o \
	${TESTDIR}/tests/testRunner.o \
	${TESTDIR}/tests/testWalls.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/micromouse-maze

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/micromouse-maze: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/micromouse-maze ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/list.o: list.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/list.o list.c

${OBJECTDIR}/main.o: main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/maze.o: maze.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/maze.o maze.c

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/gtest/src/gtest-all.o ${TESTDIR}/tests/testCosts.o ${TESTDIR}/tests/testDirection.o ${TESTDIR}/tests/testList.o ${TESTDIR}/tests/testLocation.o ${TESTDIR}/tests/testMaze.o ${TESTDIR}/tests/testRunner.o ${TESTDIR}/tests/testWalls.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} 


${TESTDIR}/gtest/src/gtest-all.o: gtest/src/gtest-all.cc 
	${MKDIR} -p ${TESTDIR}/gtest/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -I../../micromouse/micromouse-maze/gtest -MMD -MP -MF "$@.d" -o ${TESTDIR}/gtest/src/gtest-all.o gtest/src/gtest-all.cc


${TESTDIR}/tests/testCosts.o: tests/testCosts.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -I../../micromouse/micromouse-maze/gtest -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/testCosts.o tests/testCosts.cpp


${TESTDIR}/tests/testDirection.o: tests/testDirection.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -I../../micromouse/micromouse-maze/gtest -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/testDirection.o tests/testDirection.cpp


${TESTDIR}/tests/testList.o: tests/testList.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -I../../micromouse/micromouse-maze/gtest -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/testList.o tests/testList.cpp


${TESTDIR}/tests/testLocation.o: tests/testLocation.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -I../../micromouse/micromouse-maze/gtest -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/testLocation.o tests/testLocation.cpp


${TESTDIR}/tests/testMaze.o: tests/testMaze.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -I../../micromouse/micromouse-maze/gtest -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/testMaze.o tests/testMaze.cpp


${TESTDIR}/tests/testRunner.o: tests/testRunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -I../../micromouse/micromouse-maze/gtest -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/testRunner.o tests/testRunner.cpp


${TESTDIR}/tests/testWalls.o: tests/testWalls.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -I../../micromouse/micromouse-maze/gtest -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/testWalls.o tests/testWalls.cpp


${OBJECTDIR}/list_nomain.o: ${OBJECTDIR}/list.o list.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/list.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/list_nomain.o list.c;\
	else  \
	    ${CP} ${OBJECTDIR}/list.o ${OBJECTDIR}/list_nomain.o;\
	fi

${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_nomain.o main.c;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

${OBJECTDIR}/maze_nomain.o: ${OBJECTDIR}/maze.o maze.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/maze.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/maze_nomain.o maze.c;\
	else  \
	    ${CP} ${OBJECTDIR}/maze.o ${OBJECTDIR}/maze_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/micromouse-maze

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
