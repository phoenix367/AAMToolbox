################################################################################
# GTest
# See: http://code.google.com/p/googletest/
################################################################################

if(NOT ANDROID)
    find_package(Threads)
endif()

set(GTEST_HAS_PTHREAD "")

if(ANDROID OR APPLE)
    set(GTEST_HAS_CLONE 0)
else()
    set(GTEST_HAS_CLONE 1)
endif()

if(ANDROID) # Cannot use try_run when crosscompiling
    set(GTEST_HAS_PTHREAD 1)
elseif(CMAKE_USE_PTHREADS_INIT)  # The pthreads library is available and allowed.
    set(GTEST_HAS_PTHREAD 1)
else()
    set(GTEST_HAS_PTHREAD 0)
endif()

set(GTEST_DIR ${CONTRIBUTE_DIRECTORY}/gtest)
set(GTEST_INCLUDE_DIRECTORIES ${GTEST_DIR}/include ${GTEST_DIR} ${GTEST_DIR}/src)

include_directories(${GTEST_INCLUDE_DIRECTORIES})

add_library(gtest STATIC ${GTEST_DIR}/src/gtest-all.cc ${GTEST_DIR}/src/gtest_main.cc)

set_target_properties(gtest PROPERTIES COMPILE_FLAGS "-DGTEST_HAS_PTHREAD=${GTEST_HAS_PTHREAD} -DGTEST_HAS_CLONE=${GTEST_HAS_CLONE}")
