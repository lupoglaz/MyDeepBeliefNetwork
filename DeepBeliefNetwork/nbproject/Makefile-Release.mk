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
FC=g77
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/cDBN.o \
	${OBJECTDIR}/cRBLayer.o \
	${OBJECTDIR}/cTrainingSet.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-DEIGEN_NO_DEBUG
CXXFLAGS=-DEIGEN_NO_DEBUG

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../../../../Projects/Shark/lib -L../../../../Programs/boost_1_53_0/libs -lshark

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/deepbeliefnetwork

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/deepbeliefnetwork: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/deepbeliefnetwork ${OBJECTFILES} ${LDLIBSOPTIONS} -lboost_serialization -lboost_system -lboost_filesystem -lboost_program_options -lshark

${OBJECTDIR}/cDBN.o: cDBN.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../../../Programs/eigen -I../../../../Programs/boost_1_53_0 -I../../../../Projects/Shark/include -DEIGEN_NO_DEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/cDBN.o cDBN.cpp

${OBJECTDIR}/cRBLayer.o: cRBLayer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../../../Programs/eigen -I../../../../Programs/boost_1_53_0 -I../../../../Projects/Shark/include -DEIGEN_NO_DEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/cRBLayer.o cRBLayer.cpp

${OBJECTDIR}/cTrainingSet.o: cTrainingSet.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../../../Programs/eigen -I../../../../Programs/boost_1_53_0 -I../../../../Projects/Shark/include -DEIGEN_NO_DEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/cTrainingSet.o cTrainingSet.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../../../Programs/eigen -I../../../../Programs/boost_1_53_0 -I../../../../Projects/Shark/include -DEIGEN_NO_DEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/deepbeliefnetwork

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
