# Copyright (C) 2017 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

enable_testing()

file(GLOB_RECURSE tests_sources "*.cpp")
file(GLOB_RECURSE tests_headers "*.h")

#add_executable(core3tests ${tests_headers} ${tests_sources})
add_library(core3tests ${tests_headers} ${tests_sources})

add_dependencies(core3tests gmock core3lib)

#target_link_libraries(core3tests gmock core3lib db3 conf3 web3 status3 ping3 login3 chat3 core3terrain core3templates core3pathfinding idlobjects ${ENGINE3_LIBRARIES} ${ZLIB_LIBRARIES} Threads::Threads ${MYSQL_CLIENT_LIBS} ${LUA_LIBRARIES} ${DB_LIBRARIES} ${CMAKE_DL_LIBS} ${OPENSSL_LIBRARIES})

add_test(core3tests
        COMMAND $<TARGET_FILE:core3> runUnitTests
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)

