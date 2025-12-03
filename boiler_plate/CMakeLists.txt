cmake_minimum_required(VERSION 3.16)
project(CPPProcess_standalone)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
    -Wall
    #    -Wextra
    #    -Wconversion
    #    -Wsign-conversion
        -Wfloat-conversion
)

#add_definitions(-D__CADNA)

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -gdwarf-4 -fsanitize=address")

set(CMAKE_CXX_FLAGS_PROFILE "-O1 -g -gdwarf-4 -fno-omit-frame-pointer ")

set(CMAKE_CXX_FLAGS_RELEASE "-O3 ")

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Profile" CACHE STRING "" FORCE)

find_library(CADNA_LIBRARY NAMES cadnaC PATHS /usr/local/lib)
if(NOT CADNA_LIBRARY)
    message(FATAL_ERROR "CADNA library not found. Please install CADNA or specify its location.")
else()
    message(STATUS "Found CADNA library at ${CADNA_LIBRARY}")
endif()

add_executable(CPPProcess_standalone main.cpp
        src/boilerplate/typeTraits.h
        src/boilerplate/Complex.h
        src/boilerplate/MemoryBuffers.h
        src/accesses/includeAcesses.h
        src/boilerplate/commonNums.h
        src/boilerplate/fillers.h
        src/boilerplate/Parameters_sm.cc
        src/boilerplate/read_slha.cc
        src/color_sum.cc
        src/CPPProcess.cc
        src/color_sum.h
        src/boilerplate/repair_momenta.h
       	src/boilerplate/promiseTypes.h)
target_link_libraries(CPPProcess_standalone PRIVATE cadnaC c++)

