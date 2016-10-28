#
# Author    : huang li long <huanglilongwk@gmail.com>
# Time      : 2016/10/07
#

cmake_minimum_required(VERSION 3.2)
project(project CXX)

# enable c++14
list(APPEND CMAKE_CXX_FLAGS "-std=c++14")

# build type -- debug
set(CMAKE_BUILD_TYPE Debug)

# include header file path 
include_directories(
    ${PROJECT_SOURCE_DIR}
)

# collect all source files, using relative file path
file(GLOB SRCS
    RELATIVE ${PROJECT_SOURCE_DIR}
    "*.cpp"
)

# add execuble 
foreach(SRC ${SRCS})
    string(REPLACE ".cpp" "" SRC_BASE ${SRC})   # get source file's basename
    add_executable(${SRC_BASE} ${SRC})
endforeach()
