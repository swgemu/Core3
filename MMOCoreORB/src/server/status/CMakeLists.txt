# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

# Add status sources
file(GLOB_RECURSE status3_sources "*.cpp")
file(GLOB_RECURSE status3_headers "*.h")

# Add status includes
include_directories(../..)

# Create status library
add_library(status3 STATIC ${status3_sources} ${status3_headers})

add_dependencies(status3 idlobjects)