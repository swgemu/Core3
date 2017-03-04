# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

cmake_minimum_required(VERSION 2.6)

project(core3)

# Set cmake paths
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/build/unix/cmake/Modules/")

# Add lua includes and libraries
include_directories(/usr/include/lua5.1)
link_directories(/usr/local/lib)

# Find mysql includes and libraries
find_package(MySql REQUIRED)
include_directories(${MYSQL_INCLUDE_DIR})
link_directories(${MYSQL_LIBRARY})

# Find berkeley includes and libraries
find_package(Berkeley REQUIRED)
include_directories(${DB_INCLUDE_DIR})
link_directories(${DB_LIBRARIES})

# Find engine3 includes and libraries
find_package(Engine3 REQUIRED)
include_directories(${ENGINE3_INCLUDE_DIR})
link_directories(${ENGINE3_LIBRARY})

# Compile idl sources
#file(GLOB_RECURSE idls "${CMAKE_SOURCE_DIR}/src/*.idl")
#set(auto_sources)
#set(auto_headers)
#foreach(idl ${idls})
#	string(REPLACE "src/" "src/autogen/" auto_base ${idl})
#	string(REPLACE ".idl" ".cpp" auto_cpp ${auto_base})
#	string(REPLACE ".idl" ".h" auto_h ${auto_base})
#	set(auto_sources ${auto_sources} "${auto_cpp}")
#	set(auto_headers ${auto_headers} "${auto_cpp}")
#endforeach()
#add_custom_target(idl ALL
#	${IDLC_BIN_DIR}/idlc ${IDL_DIRECTIVES}
#	COMMENT "Compiling IDL sources")

#add_custom_target(cleanidl
#	${IDLC_BIN_DIR}/idlc -rebuild ${IDL_DIRECTIVES}
#	COMMENT "Rebuilding IDL sources")

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/autogen)
include_directories(${CMAKE_SOURCE_DIR}/utils)
include_directories(${CMAKE_SOURCE_DIR}/utils/gtest-1.6.0/include)
include_directories(${CMAKE_SOURCE_DIR}/utils/gmock-1.6.0/include)
link_directories(${CMAKE_SOURCE_DIR}/utils/gtest-1.6.0/lib)

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

