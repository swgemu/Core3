# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

include_directories(.)

file(GLOB_RECURSE core3client_sources "*.cpp")

# Create core3 binary
add_executable(core3client ${core3client_sources})

add_dependencies(core3client idlobjects)

target_link_libraries(core3client ${ENGINE3_LIBRARIES} ${ZLIB_LIBRARIES} Threads::Threads ${MYSQL_CLIENT_LIBS} ${LUA_LIBRARIES} ${DB_LIBRARIES} ${CMAKE_DL_LIBS} ${OPENSSL_LIBRARIES})

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/core3client DESTINATION bin)