# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

# Add zone sources
file(GLOB_RECURSE zone3_sources "*.cpp") 

# Add zone includes
include_directories(../..)

# Exclude sources from zone
file(GLOB_RECURSE zone3_excludes
    "objects/player/sessions/StructureStatusSession.cpp"
    "managers/structure/StructureManagerImplementation.cpp"
    )
list(REMOVE_ITEM zone3_sources ${zone3_excludes})

# Create zone library
add_library(zone3 SHARED ${zone3_sources})
#add_dependencies(zone3 login3)
