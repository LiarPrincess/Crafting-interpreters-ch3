cmake_minimum_required(VERSION 3.0)

project(Lox)

# Tested only on Clang
if(NOT ${CMAKE_C_COMPILER_ID} MATCHES "AppleClang|Clang")
  message(FATAL_ERROR "Unsupported compiler: " ${CMAKE_C_COMPILER_ID})
endif()

# Debug by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
  message(STATUS "Setting build type to '${CMAKE_BUILD_TYPE}' as none was specified.")
endif()

# Executable
file(GLOB_RECURSE sources "Sources/*.c")
file(GLOB_RECURSE headers "Sources/*.h")
set(executable_name ${PROJECT_NAME}-${CMAKE_BUILD_TYPE})
add_executable(${executable_name} ${sources} ${headers} "Sources/main.c")

# Flags
list(APPEND cflags -x c -arch x86_64 --std=c11)
list(APPEND cflags -Wall -Wextra -Wno-unused-parameter -Wno-newline-eof -Werror)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  message(STATUS "Adding debug flags")
  list(APPEND cflags -g -O0)
endif()

target_compile_options(${executable_name} PRIVATE ${cflags})
