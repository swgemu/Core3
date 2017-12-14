# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

# Add conf sources
file(GLOB_RECURSE core3templates_sources "*.cpp")
file(GLOB_RECURSE core3templates_headers "*.h")

# Add conf includes
include_directories(../)

# Create conf library
add_library(core3templates STATIC ${core3templates_sources} ${core3templates_headers})

add_dependencies(core3templates idlobjects)
