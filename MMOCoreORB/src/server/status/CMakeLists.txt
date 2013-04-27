# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

# Add status sources
file(GLOB_RECURSE status3_sources "*.cpp") 

# Add status includes
include_directories(../..)

# Create status library
add_library(status3 SHARED ${status3_sources})
