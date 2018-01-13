# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(core3 CXX C)

# Set cmake paths
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Set cpp requirements
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set up options
option(BUILD_IDL "Generate idl c++ sources with cmake" ON) # Enabled by default
option(IDL_NOPRELOCKS "Disables all prelock annotations" OFF) # Disabled by default
option(ENABLE_CCACHE "Enables ccache search and usage" OFF) # Disabled by default
option(RUN_GIT "Runs git log to dump last commit messages into rev.txt" OFF) # Disabled by default
option(COMPILE_TESTS "Enables mock generation in idlc and test compiling" ON) # Enabled by default
option(LOGIN_SERVER_EXTRA_PORTS "Enables login server with extra ports config" OFF) # Disabled by default

# Add lua includes and libraries
find_package(Lua "5.3" REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

# Find mysql includes and libraries
find_package(MySql REQUIRED)
#include_directories(${MYSQL_INCLUDE_DIR}) already included in find

# Find berkeley includes and libraries
find_package(Berkeley REQUIRED)
include_directories(${DB_INCLUDE_DIR})

find_package(Java 1.5 COMPONENTS Runtime REQUIRED )

# Find engine3 includes and libraries
find_package(Engine3 REQUIRED)
include_directories(${ENGINE3_INCLUDE_DIR})

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

find_package(ZLIB REQUIRED)
include_directories(${ZLIB_INCLUDE_DIRS})

# Find and set -pthreads
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost QUIET OPTIONAL_COMPONENTS thread)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

find_package(Git QUIET)

if(ENABLE_CCACHE)
    find_program(CCACHE_FOUND ccache)

    if(CCACHE_FOUND)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
    endif(CCACHE_FOUND)
endif(ENABLE_CCACHE)

if(IDL_NOPRELOCKS)
    set(IDL_DIRECTIVES ${IDL_DIRECTIVES} -noprelocks)
endif(IDL_NOPRELOCKS)

# Include googlemock and googletest
if(COMPILE_TESTS)
    add_subdirectory(utils/googletest-release-1.8.0/googlemock)

    include_directories(${CMAKE_SOURCE_DIR}/utils/googletest-release-1.8.0/googletest/include)
    include_directories(${CMAKE_SOURCE_DIR}/utils/googletest-release-1.8.0/googlemock/include)

    add_definitions(-DCOMPILE_CORE3_TESTS)
else(COMPILE_TESTS)
    set(IDL_DIRECTIVES ${IDL_DIRECTIVES} -nomocks)
endif(COMPILE_TESTS)

if (LOGIN_SERVER_EXTRA_PORTS)
    add_definitions(-DUSE_RANDOM_EXTRA_PORTS)
endif(LOGIN_SERVER_EXTRA_PORTS)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/autogen)
include_directories(${CMAKE_SOURCE_DIR}/utils)

# Define global build gcc compatible flags
set(GCCEXTRAFLAGS "-Wall -Wextra -Wno-unused -Wno-sign-compare -Wno-multichar -Wno-unused-parameter -Wno-overloaded-virtual -Wno-missing-declarations -Werror -ggdb")

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${GCCEXTRAFLAGS})
endif()


add_definitions(-DDEFAULT_DYNAMIC_CAST)

add_subdirectory(src)
add_subdirectory(src/conf)
add_subdirectory(src/terrain)
add_subdirectory(src/templates)
add_subdirectory(src/pathfinding)
add_subdirectory(src/server/db)
add_subdirectory(src/server/status)
add_subdirectory(src/server/web)
add_subdirectory(src/server/ping)
add_subdirectory(src/server/login)
add_subdirectory(src/server/chat)
add_subdirectory(src/client)
