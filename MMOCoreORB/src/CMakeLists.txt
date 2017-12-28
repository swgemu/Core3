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
link_directories(${CMAKE_BINARY_DIR}/src/server/chat)

if(BUILD_IDL)
	file(GLOB_RECURSE idls "${CMAKE_SOURCE_DIR}/src/*.idl")

	set(autogen_sources)

	foreach(idl ${idls})
		string(REPLACE "src/" "src/autogen/" autogen_base ${idl})
		string(REPLACE ".idl" ".cpp" autogen_cpp ${autogen_base})

		set(autogen_sources ${autogen_sources} "${autogen_cpp}")

		string(REGEX REPLACE ".+\/src\/" "" idl_f ${idl})
		string(CONCAT idl_b "src/" ${idl_f})

		get_filename_component(idl_we ${idl} NAME_WE)

		add_custom_command(OUTPUT "${autogen_cpp}" #"${autogen_h}"
			COMMAND ${Java_JAVA_EXECUTABLE} ${IDLC_JAVA_ARGS} ${IDL_DIRECTIVES} -silence -rbcpp -sd src ${idl_f}
			WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
			DEPENDS ${idl}
			COMMENT "Building IDL object ${idl_b}"
			VERBATIM)
	endforeach()

	set_source_files_properties(${${autogen_sources}}} PROPERTIES GENERATED TRUE)

	add_library(idlobjects STATIC ${autogen_sources})
else(BUILD_IDL)
	file(GLOB_RECURSE autogen_sources "autogen/*.cpp")
	file(GLOB_RECURSE autogen_headers "autogen/*.h")

	add_library(idlobjects STATIC ${autogen_sources} ${autogen_headers})
endif()

set_target_properties(idlobjects PROPERTIES LINKER_LANGUAGE CXX)

file(GLOB_RECURSE zone3_sources "server/zone/*.cpp")
file(GLOB_RECURSE zone3_headers "server/zone/*.h")

file(GLOB_RECURSE tre3_sources "tre3/*.cpp")
file(GLOB_RECURSE tre3_headers "tre3/*.h")

# Create core3 binary
add_executable(core3 main.cpp server/ServerCore.cpp ${tre3_sources} ${tre3_headers} ${zone3_sources} ${zone3_headers})

if(COMPILE_TESTS)
	add_dependencies(core3 gmock idlobjects)
else(COMPILE_TESTS)
	add_dependencies(core3 idlobjects)
endif(COMPILE_TESTS)

set(whole_archive_start)
set(whole_archive_end)

# Add custom link options
if(APPLE)
	set(whole_archive_start "-Wl,-all_load")
	set(whole_archive_end "") #-Wl,-noall_load deprecated
elseif(UNIX)
	set(whole_archive_start "-Wl,--whole-archive")
	set(whole_archive_end "-Wl,--no-whole-archive")
endif()

set(core3tests_libs)
set(gmock_libs)

if(COMPILE_TESTS)
	# Define tests
	enable_testing()

	file(GLOB_RECURSE tests_sources "tests/*.cpp")
	file(GLOB_RECURSE tests_headers "tests/*.h")

	add_library(core3tests ${tests_headers} ${tests_sources})

	add_dependencies(core3tests gmock idlobjects)

	set(core3tests_libs core3tests)
	set(gmock_libs gmock)
endif(COMPILE_TESTS)

target_link_libraries(core3
	${whole_archive_start}
	${core3tests_libs} db3 conf3 web3 status3 ping3 login3 chat3 core3terrain core3templates core3pathfinding idlobjects
	${whole_archive_end}
	${ENGINE3_LIBRARIES}
	${gmock_libs} ${Boost_LIBRARIES} Threads::Threads ${MYSQL_CLIENT_LIBS} ${LUA_LIBRARIES} ${DB_LIBRARIES} ${OPENSSL_LIBRARIES} ${ZLIB_LIBRARIES} ${CMAKE_DL_LIBS})

# Copy core3 binary
add_custom_command(
	TARGET core3 POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	$<TARGET_FILE:core3>
	${CMAKE_SOURCE_DIR}/bin/)

if(GIT_FOUND AND RUN_GIT)
    add_custom_command(
        TARGET core3 POST_BUILD
        COMMAND ${GIT_EXECUTABLE} log --pretty=format:"%h was %an, %ar, message: %s" -10 > ${CMAKE_SOURCE_DIR}/bin/conf/rev.txt
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		VERBATIM)
endif()

if(COMPILE_TESTS)
	add_test(core3
		COMMAND $<TARGET_FILE:core3> runUnitTests
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)
endif(COMPILE_TESTS)


#add_subdirectory(tests)