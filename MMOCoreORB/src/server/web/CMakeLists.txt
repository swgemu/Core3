# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

# Add web sources
file(GLOB_RECURSE web3_sources "*.cpp") 

# Add web includes
include_directories(../..)

# Create web library
add_library(web3 SHARED ${web3_sources} mongoose/mongoose.c)
