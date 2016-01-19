# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

# Add core3 includes
include_directories(.)
include_directories(autogen)

# Add shared core3 libraries
link_directories(${CMAKE_BINARY_DIR}/src/server/db)
link_directories(${CMAKE_BINARY_DIR}/src/server/conf)
link_directories(${CMAKE_BINARY_DIR}/src/server/web)
link_directories(${CMAKE_BINARY_DIR}/src/server/status)
link_directories(${CMAKE_BINARY_DIR}/src/server/ping)
link_directories(${CMAKE_BINARY_DIR}/src/server/login)
link_directories(${CMAKE_BINARY_DIR}/src/server/zone)
link_directories(${CMAKE_BINARY_DIR}/src/server/chat)

file(GLOB_RECURSE autogen_sources "autogen/*.cpp")

# Create core3 binary
add_executable(core3 main.cpp server/ServerCore.cpp tre3/TreeFile.cpp ${autogen_sources})
add_dependencies(core3 zone3)

# Add libraries
target_link_libraries(core3
        z crypto ssl pthread
        db-5.0 ${MYSQL_LIBRARIES}
        db3 conf3 web3 status3 ping3 login3 zone3 chat3
        ${ENGINE3_LIBRARIES} lua gtest)

# Install core3 binary
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/core3 DESTINATION bin)

