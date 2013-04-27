# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

# Add conf sources
file(GLOB_RECURSE conf3_sources "*.cpp") 

# Add conf includes
include_directories(../..)

# Create conf library
add_library(conf3 SHARED ${conf3_sources})
