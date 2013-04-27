# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

# Add db sources
file(GLOB_RECURSE db3_sources "*.cpp") 

# Add db includes
include_directories(../..)

# Create db library
add_library(db3 SHARED ${db3_sources})
