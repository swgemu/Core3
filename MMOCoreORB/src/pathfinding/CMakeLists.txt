# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

# Add conf sources
file(GLOB_RECURSE core3pathfinding_sources "*.cpp")
file(GLOB_RECURSE core3pathfinding_headers "*.h")

# Add conf includes
include_directories(../)

# Create conf library
add_library(core3pathfinding STATIC ${core3pathfinding_sources} ${core3pathfinding_headers})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")

add_dependencies(core3pathfinding idlobjects)