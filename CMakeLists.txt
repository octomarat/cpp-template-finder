# One of the following set of variables is expected
# 1) To build using llvm built from sources (and not installed)
# LLVM_SRC_PATH -- path to llvm+clang source files directory
# LLVM_BUILD_PATH -- path to llvm+clang build directory
# 2) To build using pre-built binaries
# LLVM_PATH -- path to folder with pre-built llvm+clang files

cmake_minimum_required(VERSION 2.8.2)

project(cpp-templates_finder)

# ==== GoogleTest ====

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

# ===================

if(LLVM_PATH)
    link_directories(${LLVM_PATH}/lib)
    include_directories(${LLVM_PATH}/include)
elseif(LLVM_BUILD_PATH AND LLVM_SRC_PATH)
    link_directories(${LLVM_BUILD_PATH}/lib)
    include_directories(${LLVM_SRC_PATH}/include)
    include_directories(${LLVM_BUILD_PATH}/include)
    include_directories(${LLVM_SRC_PATH}/tools/clang/include)
    include_directories(${LLVM_BUILD_PATH}/tools/clang/include)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -fno-rtti")

add_subdirectory(src bin/src)

enable_testing()
add_subdirectory(test bin/test)

file(COPY ${CMAKE_SOURCE_DIR}/test/data DESTINATION ${CMAKE_BINARY_DIR}/bin/test/)
