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

# Define build flags
set(CMAKE_CXX_FLAGS "-ggdb -Wall -Wextra -Wno-unused -Wno-unused-paramater -Wno-sign-compare -Wno-multichar -Wno-overloaded-virtual")

# Define sources
add_subdirectory(src)
add_subdirectory(src/server/conf)
add_subdirectory(src/server/db)
add_subdirectory(src/server/status)
add_subdirectory(src/server/web)
add_subdirectory(src/server/ping)
add_subdirectory(src/server/login)
add_subdirectory(src/server/zone)
add_subdirectory(src/server/chat)

