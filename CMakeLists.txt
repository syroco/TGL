# This file is part of TGL (Trajectory Generation Library).
# Copyright (C) 2016 Institut des Systèmes Intelligents et de Robotique (ISIR)
# author(s): Ryan Lober
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 2.8)
project(TrajectoryGeneratorLibrary)
set(lib_name "tgl")
# set(CMAKE_BUILD_TYPE Release)
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

option(COMPILE_TESTS "Compile unit tests." TRUE)
option(GENERATE_DOCUMENTATION "Generate the doxygen documentation." FALSE)


list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

# Get source and header files
file(GLOB source_files ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB header_files ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)

# Find Eigen headers
find_package(Eigen REQUIRED)
find_package(EigenLgsm REQUIRED)

# Find glog (Google logging utility for C++)
find_package(Glog REQUIRED)

# Include header directories
include_directories(
${CMAKE_CURRENT_SOURCE_DIR}/include
${Eigen_INCLUDE_DIRS}
${EigenLgsm_INCLUDE_DIRS}
${GLOG_INCLUDE_DIRS}
)

# Create the tgl library
add_library(
${lib_name}
${source_files}
)

# Link libs
target_link_libraries(
${lib_name}
${GLOG_LIBRARIES}
)

# Compile tests
if(${COMPILE_TESTS})
    add_subdirectory(tests)
endif()


# Compile documentation

# add a target to generate API documentation with Doxygen
if(GENERATE_DOCUMENTATION)
    find_package(Doxygen REQUIRED)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(
        docs
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif(GENERATE_DOCUMENTATION)
