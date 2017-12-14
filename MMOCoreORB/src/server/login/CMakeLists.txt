# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

# Add login sources
file(GLOB_RECURSE login3_sources "*.cpp")
file(GLOB_RECURSE login3_headers "*.h")

# Add login includes
include_directories(../..)

# Create login library
add_library(login3 STATIC ${login3_sources} ${login3_headers})
add_dependencies(login3 idlobjects)