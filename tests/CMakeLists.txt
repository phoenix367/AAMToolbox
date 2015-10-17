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

set(AAM_TEST_EXECUTABLE aam-tests)

file(GLOB AAM_TESTS "*.h" "*.cpp")

include_directories(${AAM_PUBLIC_DIR})
add_executable(${AAM_TEST_EXECUTABLE} ${AAM_TESTS})

target_link_libraries(${AAM_TEST_EXECUTABLE} gtest aam)
add_dependencies(${AAM_TEST_EXECUTABLE} gtest aam)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${OpenCV_HEADERS} ${CMAKE_BINARY_DIR})

