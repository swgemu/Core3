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

add_library(idlobjects STATIC ${autogen_sources})

# Create core3 binary
add_executable(core3 server/ServerCore.cpp tre3/TreeFile.cpp main.cpp)
add_dependencies(core3 zone3 idlobjects)

# Add libraries
if(APPLE)
    target_link_libraries(core3
            -Wl,-all_load
            db3 conf3 web3 status3 ping3 login3 zone3 chat3 core3terrain core3templates core3pathfinding idlobjects
            -Wl,-noall_load
            ${ENGINE3_LIBRARIES}
            ${ZLIB_LIBRARIES} pthread ${MYSQL_CLIENT_LIBS} ${LUA_LIBRARIES} ${DB_LIBRARIES} dl ${OPENSSL_LIBRARIES} gtest)
elseif(UNIX)
    target_link_libraries(core3
        -Wl,--whole-archive
        db3 conf3 web3 status3 ping3 login3 zone3 chat3 core3terrain core3templates core3pathfinding idlobjects
        -Wl,--no-whole-archive
        ${ENGINE3_LIBRARIES}
        ${ZLIB_LIBRARIES} pthread ${MYSQL_CLIENT_LIBS} ${LUA_LIBRARIES} ${DB_LIBRARIES} dl ${OPENSSL_LIBRARIES} gtest)
endif()

# Install core3 binary
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/core3 DESTINATION bin)
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/client/core3client DESTINATION bin)

