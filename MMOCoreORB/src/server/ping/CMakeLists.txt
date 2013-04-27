# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

# Add ping sources
file(GLOB_RECURSE ping3_sources "*.cpp") 

# Add ping includes
include_directories(../..)

# Create ping library
add_library(ping3 SHARED ${ping3_sources})
