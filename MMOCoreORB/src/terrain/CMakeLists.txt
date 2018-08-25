# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

# Add conf sources
file(GLOB_RECURSE core3terrain_sources "*.cpp")
file(GLOB_RECURSE core3terrain_headers "*.h")

# Add conf includes
include_directories(../)
include_directories(../templates)

# Create conf library
add_library(core3terrain STATIC ${core3terrain_sources} ${core3terrain_headers})

add_dependencies(core3terrain idlobjects)