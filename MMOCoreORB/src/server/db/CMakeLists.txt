# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

# Add db sources
file(GLOB_RECURSE db3_sources "*.cpp")
file(GLOB_RECURSE db3_headers "*.h")

# Add db includes
include_directories(../..)

# Create db library
add_library(db3 STATIC ${db3_sources} ${db3_headers})

add_dependencies(db3 idlobjects)