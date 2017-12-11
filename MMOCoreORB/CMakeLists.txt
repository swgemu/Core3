# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(core3)

# Set cmake paths
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

OPTION(BUILD_IDL "Generate idl c++ sources with cmake" ON) # Enabled by default

# Add lua includes and libraries
find_package(Lua "5.3" REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

# Find mysql includes and libraries
find_package(MySql REQUIRED)
include_directories(${MYSQL_INCLUDE_DIR})

# Find berkeley includes and libraries
find_package(Berkeley REQUIRED)
include_directories(${DB_INCLUDE_DIR})

find_package(Java COMPONENTS Runtime REQUIRED)

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

#find_program(CCACHE_FOUND ccache)
#if(CCACHE_FOUND)
#    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
#    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
#endif(CCACHE_FOUND)

#SET(IDL_DIRECTIVES ${IDL_DIRECTIVES} -noprelocks)

#add_custom_target(cleanidl
#	${IDLC_BIN_DIR}/idlc -rebuild ${IDL_DIRECTIVES}
#	COMMENT "Rebuilding IDL sources")

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/autogen)
include_directories(${CMAKE_SOURCE_DIR}/utils)
include_directories(${CMAKE_SOURCE_DIR}/utils/googletest-release-1.8.0/googletest/include)
include_directories(${CMAKE_SOURCE_DIR}/utils/googletest-release-1.8.0/googlemock/include)
link_directories(${CMAKE_SOURCE_DIR}/utils/googletest-release-1.8.0/googlemock/lib)

# Define build flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -Wall -Wextra -Wno-unused -Wno-sign-compare -Wno-multichar -DDEFAULT_DYNAMIC_CAST -Wno-unused-parameter -Wno-overloaded-virtual -Wno-missing-declarations -Werror -std=c++11")

# Define sources
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
add_subdirectory(src/server/zone)
add_subdirectory(src/server/chat)
add_subdirectory(src/client)

