# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

# Add core3 includes
include_directories(.)
include_directories(autogen)

# Add shared core3 libraries
link_directories(${CMAKE_BINARY_DIR}/src/server/db)
link_directories(${CMAKE_BINARY_DIR}/src/conf)
link_directories(${CMAKE_BINARY_DIR}/src/terrain)
link_directories(${CMAKE_BINARY_DIR}/src/templates)
link_directories(${CMAKE_BINARY_DIR}/src/server/web)
link_directories(${CMAKE_BINARY_DIR}/src/server/status)
link_directories(${CMAKE_BINARY_DIR}/src/server/ping)
link_directories(${CMAKE_BINARY_DIR}/src/server/login)
link_directories(${CMAKE_BINARY_DIR}/src/server/zone)
link_directories(${CMAKE_BINARY_DIR}/src/server/chat)

file(GLOB_RECURSE autogen_sources "autogen/*.cpp")

# Create core3 binary
add_executable(core3 server/ServerCore.cpp tre3/TreeFile.cpp ${autogen_sources} main.cpp)
add_dependencies(core3 zone3)

# Add libraries
target_link_libraries(core3
        db3 conf3 web3 status3 ping3 login3 zone3 chat3 core3terrain core3templates core3pathfinding
        ${ENGINE3_LIBRARIES}
        z pthread ${MYSQL_LIBRARIES} lua db-5.3 dl crypto ssl gtest)

# Install core3 binary
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/core3 DESTINATION bin)

