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
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/ShapeAppearanceData.o \
	${OBJECTDIR}/src/TrainModelInfo.o \
	${OBJECTDIR}/src/TrainModelLoader.o \
	${OBJECTDIR}/src/AppearanceDataIC.o \
	${OBJECTDIR}/contribute/dlib/stack_trace.o \
	${OBJECTDIR}/src/AAMEstimator.o \
	${OBJECTDIR}/src/TrainIC2D.o \
	${OBJECTDIR}/src/OptimHelper2D.o \
	${OBJECTDIR}/src/TrainConventional.o \
	${OBJECTDIR}/src/PiecewiseWarp.o \
	${OBJECTDIR}/src/AAMModel.o \
	${OBJECTDIR}/src/AppearanceData.o \
	${OBJECTDIR}/src/TrainStrategy.o \
	${OBJECTDIR}/src/ShapeData.o \
	${OBJECTDIR}/src/AAMFunctions2D.o \
	${OBJECTDIR}/src/ICAAMModel.o \
	${OBJECTDIR}/src/CommonFunctions.o \
	${OBJECTDIR}/src/AAMFunctions3D.o

# Test Directory
TESTDIR=build/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f16 \
	${TESTDIR}/TestFiles/f21 \
	${TESTDIR}/TestFiles/f3 \
	${TESTDIR}/TestFiles/f23 \
	${TESTDIR}/TestFiles/f15 \
	${TESTDIR}/TestFiles/f8 \
	${TESTDIR}/TestFiles/f13 \
	${TESTDIR}/TestFiles/f25 \
	${TESTDIR}/TestFiles/f28 \
	${TESTDIR}/TestFiles/f11 \
	${TESTDIR}/TestFiles/f31 \
	${TESTDIR}/TestFiles/f6 \
	${TESTDIR}/TestFiles/f7 \
	${TESTDIR}/TestFiles/f18 \
	${TESTDIR}/TestFiles/f20 \
	${TESTDIR}/TestFiles/f27 \
	${TESTDIR}/TestFiles/f9 \
	${TESTDIR}/TestFiles/f14 \
	${TESTDIR}/TestFiles/f26 \
	${TESTDIR}/TestFiles/f4 \
	${TESTDIR}/TestFiles/f5 \
	${TESTDIR}/TestFiles/f29 \
	${TESTDIR}/TestFiles/f12 \
	${TESTDIR}/TestFiles/f17 \
	${TESTDIR}/TestFiles/f19 \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f22 \
	${TESTDIR}/TestFiles/f24 \
	${TESTDIR}/TestFiles/f10

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-O0
CXXFLAGS=-O0

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lopencv_core -lopencv_imgproc -lopencv_highgui -lboost_math_c99f -lboost_thread

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux-x86/libAAMToolbox.so

dist/Debug/GNU-Linux-x86/libAAMToolbox.so: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} -shared -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libAAMToolbox.so -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/ShapeAppearanceData.o: src/ShapeAppearanceData.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ShapeAppearanceData.o src/ShapeAppearanceData.cpp

${OBJECTDIR}/src/TrainModelInfo.o: src/TrainModelInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TrainModelInfo.o src/TrainModelInfo.cpp

${OBJECTDIR}/src/TrainModelLoader.o: src/TrainModelLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TrainModelLoader.o src/TrainModelLoader.cpp

${OBJECTDIR}/src/AppearanceDataIC.o: src/AppearanceDataIC.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AppearanceDataIC.o src/AppearanceDataIC.cpp

${OBJECTDIR}/contribute/dlib/stack_trace.o: contribute/dlib/stack_trace.cpp 
	${MKDIR} -p ${OBJECTDIR}/contribute/dlib
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/contribute/dlib/stack_trace.o contribute/dlib/stack_trace.cpp

${OBJECTDIR}/src/AAMEstimator.o: src/AAMEstimator.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AAMEstimator.o src/AAMEstimator.cpp

${OBJECTDIR}/src/TrainIC2D.o: src/TrainIC2D.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TrainIC2D.o src/TrainIC2D.cpp

${OBJECTDIR}/src/OptimHelper2D.o: src/OptimHelper2D.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/OptimHelper2D.o src/OptimHelper2D.cpp

${OBJECTDIR}/src/TrainConventional.o: src/TrainConventional.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TrainConventional.o src/TrainConventional.cpp

${OBJECTDIR}/src/PiecewiseWarp.o: src/PiecewiseWarp.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/PiecewiseWarp.o src/PiecewiseWarp.cpp

${OBJECTDIR}/src/AAMModel.o: src/AAMModel.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AAMModel.o src/AAMModel.cpp

${OBJECTDIR}/src/AppearanceData.o: src/AppearanceData.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AppearanceData.o src/AppearanceData.cpp

${OBJECTDIR}/src/TrainStrategy.o: src/TrainStrategy.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TrainStrategy.o src/TrainStrategy.cpp

${OBJECTDIR}/src/ShapeData.o: src/ShapeData.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ShapeData.o src/ShapeData.cpp

${OBJECTDIR}/src/AAMFunctions2D.o: src/AAMFunctions2D.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AAMFunctions2D.o src/AAMFunctions2D.cpp

${OBJECTDIR}/src/ICAAMModel.o: src/ICAAMModel.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ICAAMModel.o src/ICAAMModel.cpp

${OBJECTDIR}/src/CommonFunctions.o: src/CommonFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/CommonFunctions.o src/CommonFunctions.cpp

${OBJECTDIR}/src/AAMFunctions3D.o: src/AAMFunctions3D.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AAMFunctions3D.o src/AAMFunctions3D.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f16: ${TESTDIR}/tests/aamestimatorTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f16 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f21: ${TESTDIR}/tests/atransformTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f21 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/aldataTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f23: ${TESTDIR}/tests/aplymodelicTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f23 $^ ${LDLIBSOPTIONS} -lopencv_objdetect 

${TESTDIR}/TestFiles/f15: ${TESTDIR}/tests/aplymodelTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f15 $^ ${LDLIBSOPTIONS} -lopencv_objdetect 

${TESTDIR}/TestFiles/f8: ${TESTDIR}/tests/a2vectorTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f8 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f13: ${TESTDIR}/tests/cshaTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f13 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f25: ${TESTDIR}/tests/cjacobianTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f25 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f28: ${TESTDIR}/tests/computeSDTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f28 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f11: ${TESTDIR}/tests/cweightsTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f11 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f31: ${TESTDIR}/tests/condTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f31 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f6: ${TESTDIR}/tests/delaunayTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f6 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f7: ${TESTDIR}/tests/drobjectTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f7 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f18: ${TESTDIR}/tests/grad2DTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f18 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f20: ${TESTDIR}/tests/gsorthTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f20 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f27: ${TESTDIR}/tests/makeappICTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f27 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f9: ${TESTDIR}/tests/mappearanceTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f9 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f14: ${TESTDIR}/tests/msearchTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f14 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f26: ${TESTDIR}/tests/makeShapeICTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f26 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f4: ${TESTDIR}/tests/msmodelTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f4 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f5: ${TESTDIR}/tests/pcaTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f5 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f29: ${TESTDIR}/tests/procrustesTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f29 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f12: ${TESTDIR}/tests/reignoiseTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f12 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f17: ${TESTDIR}/tests/sloadTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f17 $^ ${LDLIBSOPTIONS} -lboost_filesystem 

${TESTDIR}/TestFiles/f19: ${TESTDIR}/tests/trainICTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f19 $^ ${LDLIBSOPTIONS} -lboost_filesystem 

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/tminfoTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/tmloadTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f22: ${TESTDIR}/tests/wcomposTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f22 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f24: ${TESTDIR}/tests/wmapTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f24 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f10: ${TESTDIR}/tests/wtriangleTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f10 $^ ${LDLIBSOPTIONS} 


${TESTDIR}/tests/aamestimatorTest.o: tests/aamestimatorTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/aamestimatorTest.o tests/aamestimatorTest.cpp


${TESTDIR}/tests/atransformTest.o: tests/atransformTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/atransformTest.o tests/atransformTest.cpp


${TESTDIR}/tests/aldataTest.o: tests/aldataTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/aldataTest.o tests/aldataTest.cpp


${TESTDIR}/tests/aplymodelicTest.o: tests/aplymodelicTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/aplymodelicTest.o tests/aplymodelicTest.cpp


${TESTDIR}/tests/aplymodelTest.o: tests/aplymodelTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/aplymodelTest.o tests/aplymodelTest.cpp


${TESTDIR}/tests/a2vectorTest.o: tests/a2vectorTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/a2vectorTest.o tests/a2vectorTest.cpp


${TESTDIR}/tests/cshaTest.o: tests/cshaTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/cshaTest.o tests/cshaTest.cpp


${TESTDIR}/tests/cjacobianTest.o: tests/cjacobianTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/cjacobianTest.o tests/cjacobianTest.cpp


${TESTDIR}/tests/computeSDTest.o: tests/computeSDTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/computeSDTest.o tests/computeSDTest.cpp


${TESTDIR}/tests/cweightsTest.o: tests/cweightsTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/cweightsTest.o tests/cweightsTest.cpp


${TESTDIR}/tests/condTest.o: tests/condTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/condTest.o tests/condTest.cpp


${TESTDIR}/tests/delaunayTest.o: tests/delaunayTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/delaunayTest.o tests/delaunayTest.cpp


${TESTDIR}/tests/drobjectTest.o: tests/drobjectTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/drobjectTest.o tests/drobjectTest.cpp


${TESTDIR}/tests/grad2DTest.o: tests/grad2DTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/grad2DTest.o tests/grad2DTest.cpp


${TESTDIR}/tests/gsorthTest.o: tests/gsorthTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/gsorthTest.o tests/gsorthTest.cpp


${TESTDIR}/tests/makeappICTest.o: tests/makeappICTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/makeappICTest.o tests/makeappICTest.cpp


${TESTDIR}/tests/mappearanceTest.o: tests/mappearanceTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/mappearanceTest.o tests/mappearanceTest.cpp


${TESTDIR}/tests/msearchTest.o: tests/msearchTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/msearchTest.o tests/msearchTest.cpp


${TESTDIR}/tests/makeShapeICTest.o: tests/makeShapeICTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/makeShapeICTest.o tests/makeShapeICTest.cpp


${TESTDIR}/tests/msmodelTest.o: tests/msmodelTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/msmodelTest.o tests/msmodelTest.cpp


${TESTDIR}/tests/pcaTest.o: tests/pcaTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/pcaTest.o tests/pcaTest.cpp


${TESTDIR}/tests/procrustesTest.o: tests/procrustesTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/procrustesTest.o tests/procrustesTest.cpp


${TESTDIR}/tests/reignoiseTest.o: tests/reignoiseTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/reignoiseTest.o tests/reignoiseTest.cpp


${TESTDIR}/tests/sloadTest.o: tests/sloadTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/sloadTest.o tests/sloadTest.cpp


${TESTDIR}/tests/trainICTest.o: tests/trainICTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/trainICTest.o tests/trainICTest.cpp


${TESTDIR}/tests/tminfoTest.o: tests/tminfoTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/tminfoTest.o tests/tminfoTest.cpp


${TESTDIR}/tests/tmloadTest.o: tests/tmloadTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/tmloadTest.o tests/tmloadTest.cpp


${TESTDIR}/tests/wcomposTest.o: tests/wcomposTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/wcomposTest.o tests/wcomposTest.cpp


${TESTDIR}/tests/wmapTest.o: tests/wmapTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/wmapTest.o tests/wmapTest.cpp


${TESTDIR}/tests/wtriangleTest.o: tests/wtriangleTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -Icontribute -MMD -MP -MF $@.d -o ${TESTDIR}/tests/wtriangleTest.o tests/wtriangleTest.cpp


${OBJECTDIR}/src/ShapeAppearanceData_nomain.o: ${OBJECTDIR}/src/ShapeAppearanceData.o src/ShapeAppearanceData.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ShapeAppearanceData.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ShapeAppearanceData_nomain.o src/ShapeAppearanceData.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ShapeAppearanceData.o ${OBJECTDIR}/src/ShapeAppearanceData_nomain.o;\
	fi

${OBJECTDIR}/src/TrainModelInfo_nomain.o: ${OBJECTDIR}/src/TrainModelInfo.o src/TrainModelInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/TrainModelInfo.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TrainModelInfo_nomain.o src/TrainModelInfo.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/TrainModelInfo.o ${OBJECTDIR}/src/TrainModelInfo_nomain.o;\
	fi

${OBJECTDIR}/src/TrainModelLoader_nomain.o: ${OBJECTDIR}/src/TrainModelLoader.o src/TrainModelLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/TrainModelLoader.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TrainModelLoader_nomain.o src/TrainModelLoader.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/TrainModelLoader.o ${OBJECTDIR}/src/TrainModelLoader_nomain.o;\
	fi

${OBJECTDIR}/src/AppearanceDataIC_nomain.o: ${OBJECTDIR}/src/AppearanceDataIC.o src/AppearanceDataIC.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/AppearanceDataIC.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AppearanceDataIC_nomain.o src/AppearanceDataIC.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/AppearanceDataIC.o ${OBJECTDIR}/src/AppearanceDataIC_nomain.o;\
	fi

${OBJECTDIR}/contribute/dlib/stack_trace_nomain.o: ${OBJECTDIR}/contribute/dlib/stack_trace.o contribute/dlib/stack_trace.cpp 
	${MKDIR} -p ${OBJECTDIR}/contribute/dlib
	@NMOUTPUT=`${NM} ${OBJECTDIR}/contribute/dlib/stack_trace.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/contribute/dlib/stack_trace_nomain.o contribute/dlib/stack_trace.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/contribute/dlib/stack_trace.o ${OBJECTDIR}/contribute/dlib/stack_trace_nomain.o;\
	fi

${OBJECTDIR}/src/AAMEstimator_nomain.o: ${OBJECTDIR}/src/AAMEstimator.o src/AAMEstimator.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/AAMEstimator.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AAMEstimator_nomain.o src/AAMEstimator.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/AAMEstimator.o ${OBJECTDIR}/src/AAMEstimator_nomain.o;\
	fi

${OBJECTDIR}/src/TrainIC2D_nomain.o: ${OBJECTDIR}/src/TrainIC2D.o src/TrainIC2D.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/TrainIC2D.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TrainIC2D_nomain.o src/TrainIC2D.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/TrainIC2D.o ${OBJECTDIR}/src/TrainIC2D_nomain.o;\
	fi

${OBJECTDIR}/src/OptimHelper2D_nomain.o: ${OBJECTDIR}/src/OptimHelper2D.o src/OptimHelper2D.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/OptimHelper2D.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/OptimHelper2D_nomain.o src/OptimHelper2D.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/OptimHelper2D.o ${OBJECTDIR}/src/OptimHelper2D_nomain.o;\
	fi

${OBJECTDIR}/src/TrainConventional_nomain.o: ${OBJECTDIR}/src/TrainConventional.o src/TrainConventional.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/TrainConventional.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TrainConventional_nomain.o src/TrainConventional.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/TrainConventional.o ${OBJECTDIR}/src/TrainConventional_nomain.o;\
	fi

${OBJECTDIR}/src/PiecewiseWarp_nomain.o: ${OBJECTDIR}/src/PiecewiseWarp.o src/PiecewiseWarp.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/PiecewiseWarp.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/PiecewiseWarp_nomain.o src/PiecewiseWarp.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/PiecewiseWarp.o ${OBJECTDIR}/src/PiecewiseWarp_nomain.o;\
	fi

${OBJECTDIR}/src/AAMModel_nomain.o: ${OBJECTDIR}/src/AAMModel.o src/AAMModel.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/AAMModel.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AAMModel_nomain.o src/AAMModel.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/AAMModel.o ${OBJECTDIR}/src/AAMModel_nomain.o;\
	fi

${OBJECTDIR}/src/AppearanceData_nomain.o: ${OBJECTDIR}/src/AppearanceData.o src/AppearanceData.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/AppearanceData.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AppearanceData_nomain.o src/AppearanceData.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/AppearanceData.o ${OBJECTDIR}/src/AppearanceData_nomain.o;\
	fi

${OBJECTDIR}/src/TrainStrategy_nomain.o: ${OBJECTDIR}/src/TrainStrategy.o src/TrainStrategy.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/TrainStrategy.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TrainStrategy_nomain.o src/TrainStrategy.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/TrainStrategy.o ${OBJECTDIR}/src/TrainStrategy_nomain.o;\
	fi

${OBJECTDIR}/src/ShapeData_nomain.o: ${OBJECTDIR}/src/ShapeData.o src/ShapeData.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ShapeData.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ShapeData_nomain.o src/ShapeData.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ShapeData.o ${OBJECTDIR}/src/ShapeData_nomain.o;\
	fi

${OBJECTDIR}/src/AAMFunctions2D_nomain.o: ${OBJECTDIR}/src/AAMFunctions2D.o src/AAMFunctions2D.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/AAMFunctions2D.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AAMFunctions2D_nomain.o src/AAMFunctions2D.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/AAMFunctions2D.o ${OBJECTDIR}/src/AAMFunctions2D_nomain.o;\
	fi

${OBJECTDIR}/src/ICAAMModel_nomain.o: ${OBJECTDIR}/src/ICAAMModel.o src/ICAAMModel.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ICAAMModel.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ICAAMModel_nomain.o src/ICAAMModel.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ICAAMModel.o ${OBJECTDIR}/src/ICAAMModel_nomain.o;\
	fi

${OBJECTDIR}/src/CommonFunctions_nomain.o: ${OBJECTDIR}/src/CommonFunctions.o src/CommonFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/CommonFunctions.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/CommonFunctions_nomain.o src/CommonFunctions.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/CommonFunctions.o ${OBJECTDIR}/src/CommonFunctions_nomain.o;\
	fi

${OBJECTDIR}/src/AAMFunctions3D_nomain.o: ${OBJECTDIR}/src/AAMFunctions3D.o src/AAMFunctions3D.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/AAMFunctions3D.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iinclude -Icontribute -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AAMFunctions3D_nomain.o src/AAMFunctions3D.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/AAMFunctions3D.o ${OBJECTDIR}/src/AAMFunctions3D_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f16 || true; \
	    ${TESTDIR}/TestFiles/f21 || true; \
	    ${TESTDIR}/TestFiles/f3 || true; \
	    ${TESTDIR}/TestFiles/f23 || true; \
	    ${TESTDIR}/TestFiles/f15 || true; \
	    ${TESTDIR}/TestFiles/f8 || true; \
	    ${TESTDIR}/TestFiles/f13 || true; \
	    ${TESTDIR}/TestFiles/f25 || true; \
	    ${TESTDIR}/TestFiles/f28 || true; \
	    ${TESTDIR}/TestFiles/f11 || true; \
	    ${TESTDIR}/TestFiles/f31 || true; \
	    ${TESTDIR}/TestFiles/f6 || true; \
	    ${TESTDIR}/TestFiles/f7 || true; \
	    ${TESTDIR}/TestFiles/f18 || true; \
	    ${TESTDIR}/TestFiles/f20 || true; \
	    ${TESTDIR}/TestFiles/f27 || true; \
	    ${TESTDIR}/TestFiles/f9 || true; \
	    ${TESTDIR}/TestFiles/f14 || true; \
	    ${TESTDIR}/TestFiles/f26 || true; \
	    ${TESTDIR}/TestFiles/f4 || true; \
	    ${TESTDIR}/TestFiles/f5 || true; \
	    ${TESTDIR}/TestFiles/f29 || true; \
	    ${TESTDIR}/TestFiles/f12 || true; \
	    ${TESTDIR}/TestFiles/f17 || true; \
	    ${TESTDIR}/TestFiles/f19 || true; \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f22 || true; \
	    ${TESTDIR}/TestFiles/f24 || true; \
	    ${TESTDIR}/TestFiles/f10 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/libAAMToolbox.so

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
