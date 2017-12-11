# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

include_directories(.)

file(GLOB_RECURSE core3client_sources "*.cpp")

# Create core3 binary
add_executable(core3client ${core3client_sources})

target_link_libraries(core3client ${ENGINE3_LIBRARIES} ${ZLIB_LIBRARIES} pthread ${MYSQL_CLIENT_LIBS} ${LUA_LIBRARIES} ${DB_LIBRARIES} dl ${OPENSSL_LIBRARIES})

