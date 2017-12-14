# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

# Add web sources
file(GLOB_RECURSE web3_sources "*.cpp")
file(GLOB_RECURSE web3_headers "*.h")

# Add web includes
include_directories(../..)

# Create web library
add_library(web3 STATIC ${web3_sources} ${web3_headers} mongoose/mongoose.c)

add_dependencies(web3 idlobjects)
