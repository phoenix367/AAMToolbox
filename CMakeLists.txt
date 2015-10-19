###########################################################################
#  Active Appearance Model toolbox                                        #
#  Copyright (C) 2015 Ivan Gubochkin                                      #
#  e-mail: jhng@yandex.ru                                                 #
#                                                                         #
#   This program is free software: you can redistribute it and/or modify  #
#   it under the terms of the GNU General Public License as published by  #
#   the Free Software Foundation, either version 3 of the License, or     #
#   (at your option) any later version.                                   #
#                                                                         #
#   This program is distributed in the hope that it will be useful,       #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of        #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
#   GNU General Public License for more details.                          #
#                                                                         #
#   You should have received a copy of the GNU General Public License     #
#   along with this program.  If not, see <http://www.gnu.org/licenses/>. #
###########################################################################

cmake_minimum_required(VERSION 2.8.12.2 FATAL_ERROR)

set(the_project aam-toolbox)
project(${the_project} CXX C)
set(CPACK_PACKAGE_NAME "Active appearance model toolbox")
set(AAM_LIBRARY_NAME aam)

# The version number.
set(${the_project}_VERSION_MAJOR "0")
set(${the_project}_VERSION_MINOR "1")
set(${the_project}_VERSION_PATCH "alfa")
set(${the_project}_VERSION "${${the_project}_VERSION_MAJOR}.${${the_project}_VERSION_MINOR}.${${the_project}_VERSION_PATCH}")

option(BuildTests "Build Tests" ON)

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/cmake")

set(CONTRIBUTE_DIRECTORY "${CMAKE_SOURCE_DIR}/contribute")
set(DLIB_INCLUDE_DIRECTORY "${CONTRIBUTE_DIRECTORY}")

set(LIBRARY_OUTPUT_PATH "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

enable_testing(true)

set(AAM_TEST_DATA_PATH "${CMAKE_SOURCE_DIR}/data")
configure_file("${CMAKE_SOURCE_DIR}/test_config.h.in" "${CMAKE_BINARY_DIR}/test_config.h" NEWLINE_STYLE UNIX)

# find OpenCV
find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)

set(AAM_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(AAM_PUBLIC_DIR "${AAM_DIR}/include")
set(AAM_SOURCE_DIR "${AAM_DIR}/src")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
include_directories(${DLIB_INCLUDE_DIRECTORY} ${AAM_PUBLIC_DIR})

file(GLOB AAM_HEADERS "${AAM_PUBLIC_DIR}/*.h")
file(GLOB AAM_SOURCES "${AAM_SOURCE_DIR}/*.h" "${AAM_SOURCE_DIR}/*.cpp")

add_library(${AAM_LIBRARY_NAME} ${AAM_HEADERS} ${AAM_SOURCES})
target_link_libraries(${AAM_LIBRARY_NAME} ${CMAKE_THREAD_LIBS_INIT} ${OpenCV_LIBS})

if (BuildTests)
    include(${CMAKE_MODULE_PATH}/gtest.cmake)
endif()

if(BuildTests)
    add_subdirectory(tests)
    add_test (NAME AAM_tests COMMAND aam-tests)
endif()

