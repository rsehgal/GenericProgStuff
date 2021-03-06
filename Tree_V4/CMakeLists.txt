cmake_minimum_required(VERSION 2.8.8)
project(Tree C CXX)

#To put all the executables in build directory
#SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin) 

enable_language(CXX)

#Added to detect compiler support for C++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

################################################################################
if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type selected, default to Release")
  set(CMAKE_BUILD_TYPE "Release")
endif()
string(TOUPPER ${CMAKE_BUILD_TYPE} _build_type)

# Setting the C++ compiler to use
set("${CMAKE_CXX_COMPILER_ID}" TRUE CACHE STRING "C++ Compiler")
if (NOT GNU AND NOT Clang AND NOT Intel)
  message(WARNING "Unsupported compiler. Build will likely fail.")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/modules)

include(MacroUtilities)
################################################################################

# see if we have CCACHE ( to avoid recompilation on branch switches )
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
  message(STATUS "found ccache")
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

find_package(ROOT REQUIRED)
include_directories(AFTER SYSTEM ${ROOT_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)


file(GLOB headersGenTree ${headersGenTree} ${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h )
file(GLOB sourcesGenTree ${sourcesGenTree} ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp )

add_library(track SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/Track.cpp ${CMAKE_CURRENT_SOURCE_DIR}/inc/Track_rflx.cpp)
add_executable(TestGenTree ${CMAKE_CURRENT_SOURCE_DIR}/test/TestGenTree.cpp ${sourcesGenTree})
target_link_libraries(TestGenTree ${ROOT_LIBRARIES} -L. track -lTreePlayer)

add_executable(DetectorInfo ${CMAKE_CURRENT_SOURCE_DIR}/test/DetectorInfo.cpp ${sourcesGenTree})
target_link_libraries(DetectorInfo ${ROOT_LIBRARIES} -L. track -lTreePlayer)
