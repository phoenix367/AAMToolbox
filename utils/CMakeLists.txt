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

subdirlist(subdirs ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${OpenCV_HEADERS} ${AAM_PUBLIC_DIR} ${TCLAP_INCLUDE_DIRECTORY}
        ${CMAKE_BINARY_DIR})
set(LIB_DEPS ${AAM_LIBRARY_NAME})

foreach(__subdir ${subdirs})
    set(the_project ${__subdir})
    file(GLOB __srcs "*.hpp" "*.h" "*.cpp" "*.c" "${CMAKE_CURRENT_SOURCE_DIR}/${__subdir}/*")
    add_executable(${the_project} ${__srcs})

    target_link_libraries(${the_project} ${LIB_DEPS})
    add_dependencies(${the_project} ${LIB_DEPS})
    set_target_properties(${the_project} PROPERTIES OUTPUT_NAME "${the_project}")

    if(EnableSolutionFolders)
        set_target_properties(${the_project} PROPERTIES FOLDER "utilities")
    endif()
endforeach()

