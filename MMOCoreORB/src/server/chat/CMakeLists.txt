# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

# Add chat sources
file(GLOB_RECURSE chat3_sources "*.cpp") 

# Add chat includes
include_directories(../..)

# Create chat library
add_library(chat3 SHARED ${chat3_sources})
#add_dependencies(chat3 idl)
