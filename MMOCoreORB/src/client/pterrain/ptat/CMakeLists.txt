# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

cmake_minimum_required(VERSION 2.8)

PROJECT(ProceduralTerrain)

# set cmake find moudles path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")

# find mysql includes and libraries
find_package(MySql REQUIRED)
INCLUDE_DIRECTORIES(${MYSQL_INCLUDE_DIR})
set(LIBS ${LIBS} ${MYSQL_LIBRARY})

# find berkeley includes and libraries
find_package(Berkeley REQUIRED)
INCLUDE_DIRECTORIES(${DB_INCLUDE_DIR})
set(LIBS ${LIBS} ${DB_LIBRARIES})

# add pterrain3 sources
FILE(GLOB_RECURSE pterrain_sources "*.cpp") 

# add pterrain3 includes
INCLUDE_DIRECTORIES(.)

# create pterrain3 library
ADD_LIBRARY(pterrain ${pterrain_sources})