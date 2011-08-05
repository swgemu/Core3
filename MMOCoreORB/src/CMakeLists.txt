# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

# set cmake find moudles path
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/build/unix/cmake/Modules/")

# add lua includes and libraries
INCLUDE_DIRECTORIES(/usr/include/lua5.1)
LINK_DIRECTORIES(/usr/local/lib/lua)

# find mysql includes and libraries
find_package(MySql REQUIRED)
INCLUDE_DIRECTORIES(${MYSQL_INCLUDE_DIR})
LINK_DIRECTORIES(${MYSQL_LIBRARY})

# find berkeley includes and libraries
find_package(Berkeley REQUIRED)
INCLUDE_DIRECTORIES(${DB_INCLUDE_DIR})
LINK_DIRECTORIES(${DB_LIBRARIES})

# add core3 includes
INCLUDE_DIRECTORIES(.)

# add core3 sources
FILE(GLOB_RECURSE core3_sources "server/*.cpp") 

# add engine3 includes
INCLUDE_DIRECTORIES(../../MMOEngine/src)
LINK_DIRECTORIES(/home/oru/workspace/MMOEngine/lib/unix)

# create core3 binary
SET(CMAKE_CXX_FLAGS "-ggdb -Wextra -Wno-unused -Wno-sign-compare -Wno-multichar")
ADD_EXECUTABLE(core3 main.cpp ${core3_sources} tre3/TreeFile.cpp server/web/mongoose/mongoose.c)
TARGET_LINK_LIBRARIES(core3 engine3 z rt dl pthread db-5.0 lua mysqlclient)
