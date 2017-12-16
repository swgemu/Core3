# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(core3 CXX C)

# Set cmake paths
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

option(BUILD_IDL "Generate idl c++ sources with cmake" ON) # Enabled by default
option(IDL_NOPRELOCKS "Disables all prelock annotations" OFF) # Disabled by default
option(ENABLE_CCACHE "Enables ccache search and usage" OFF) # Disabled by default
option(RUN_GIT "Runs git log to dump last commit messages into rev.txt" OFF) # Disabled by default

# Add lua includes and libraries
find_package(Lua "5.3" REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

# Find mysql includes and libraries
find_package(MySql REQUIRED)
#include_directories(${MYSQL_INCLUDE_DIR}) already included in find

# Find berkeley includes and libraries
find_package(Berkeley REQUIRED)
include_directories(${DB_INCLUDE_DIR})

find_package(Java 1.7 COMPONENTS Runtime REQUIRED )

# Find engine3 includes and libraries
find_package(Engine3 REQUIRED)
include_directories(${ENGINE3_INCLUDE_DIR})

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

find_package(ZLIB REQUIRED)
include_directories(${ZLIB_INCLUDE_DIRS})

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

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

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/autogen)
include_directories(${CMAKE_SOURCE_DIR}/utils)
include_directories(${CMAKE_SOURCE_DIR}/utils/googletest-release-1.8.0/googletest/include)
include_directories(${CMAKE_SOURCE_DIR}/utils/googletest-release-1.8.0/googlemock/include)

# Define build flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -Wall -Wextra -Wno-unused -Wno-sign-compare -Wno-multichar -DDEFAULT_DYNAMIC_CAST -Wno-unused-parameter -Wno-overloaded-virtual -Wno-missing-declarations -Werror -std=c++11")

# Define sources
add_subdirectory(utils/googletest-release-1.8.0/googlemock)
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

