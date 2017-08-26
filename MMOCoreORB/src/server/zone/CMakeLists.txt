# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

# Add zone sources
file(GLOB_RECURSE zone3_sources "*.cpp") 

# Add zone includes
include_directories(../..)

# Create zone library
add_library(zone3 STATIC ${zone3_sources} packets/ship/PackedPosition.h objects/ship/ShipProjectileData.h packets/ship/OnShipHit.h)
#add_dependencies(zone3 login3)
