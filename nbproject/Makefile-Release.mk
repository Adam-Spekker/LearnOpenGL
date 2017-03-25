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
CND_PLATFORM=GNU-Linux
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
	${OBJECTDIR}/LearnOpenGL/Camera.o \
	${OBJECTDIR}/LearnOpenGL/Frame.o \
	${OBJECTDIR}/LearnOpenGL/Mesh.o \
	${OBJECTDIR}/LearnOpenGL/Model.o \
	${OBJECTDIR}/LearnOpenGL/Shader.o \
	${OBJECTDIR}/LearnOpenGL/Surface.o \
	${OBJECTDIR}/LearnOpenGL/main.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/learnopengl

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/learnopengl: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/learnopengl ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/LearnOpenGL/Camera.o: LearnOpenGL/Camera.cpp
	${MKDIR} -p ${OBJECTDIR}/LearnOpenGL
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LearnOpenGL/Camera.o LearnOpenGL/Camera.cpp

${OBJECTDIR}/LearnOpenGL/Frame.o: LearnOpenGL/Frame.cpp
	${MKDIR} -p ${OBJECTDIR}/LearnOpenGL
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LearnOpenGL/Frame.o LearnOpenGL/Frame.cpp

${OBJECTDIR}/LearnOpenGL/Mesh.o: LearnOpenGL/Mesh.cpp
	${MKDIR} -p ${OBJECTDIR}/LearnOpenGL
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LearnOpenGL/Mesh.o LearnOpenGL/Mesh.cpp

${OBJECTDIR}/LearnOpenGL/Model.o: LearnOpenGL/Model.cpp
	${MKDIR} -p ${OBJECTDIR}/LearnOpenGL
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LearnOpenGL/Model.o LearnOpenGL/Model.cpp

${OBJECTDIR}/LearnOpenGL/Shader.o: LearnOpenGL/Shader.cpp
	${MKDIR} -p ${OBJECTDIR}/LearnOpenGL
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LearnOpenGL/Shader.o LearnOpenGL/Shader.cpp

${OBJECTDIR}/LearnOpenGL/Surface.o: LearnOpenGL/Surface.cpp
	${MKDIR} -p ${OBJECTDIR}/LearnOpenGL
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LearnOpenGL/Surface.o LearnOpenGL/Surface.cpp

${OBJECTDIR}/LearnOpenGL/main.o: LearnOpenGL/main.cpp
	${MKDIR} -p ${OBJECTDIR}/LearnOpenGL
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LearnOpenGL/main.o LearnOpenGL/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
