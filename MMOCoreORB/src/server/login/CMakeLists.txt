# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

# Add login sources
file(GLOB_RECURSE login3_sources "*.cpp") 

# Add login includes
include_directories(../..)

# Create login library
add_library(login3 SHARED ${login3_sources})
#add_dependencies(login3 chat3)