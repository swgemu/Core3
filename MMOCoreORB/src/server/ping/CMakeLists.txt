# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

# Add ping sources
file(GLOB_RECURSE ping3_sources "*.cpp")
file(GLOB_RECURSE ping3_headers "*.h")

# Add ping includes
include_directories(../..)

# Create ping library
add_library(ping3 STATIC ${ping3_sources} ${ping3_headers})

add_dependencies(ping3 idlobjects)