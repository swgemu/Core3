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
	#set(autogen_headers)
	foreach(idl ${idls})
		string(REPLACE "src/" "src/autogen/" autogen_base ${idl})
		string(REPLACE ".idl" ".cpp" autogen_cpp ${autogen_base})
	#	string(REPLACE ".idl" ".h" autogen_h ${autogen_base})
		set(autogen_sources ${autogen_sources} "${autogen_cpp}")
	#	set(autogen_headers ${autogen_headers} "${autogen_h}")

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

	#set_source_files_properties(${${autogen_sources}} ${${autogen_headers}} PROPERTIES GENERATED TRUE)
	set_source_files_properties(${${autogen_sources}}} PROPERTIES GENERATED TRUE)

	#add_library(idlobjects STATIC ${autogen_sources} ${autogen_headers})
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
add_executable(core3 server/ServerCore.cpp ${tre3_sources} ${tre3_headers} ${zone3_sources} ${zone3_headers} main.cpp)
add_dependencies(core3 gmock idlobjects)

set(whole_archive_start)
set(whole_archive_end)
# Add libraries
if(APPLE)
	set(whole_archive_start "-Wl,-all_load")
	set(whole_archive_end "") #-Wl,-noall_load deprecated
elseif(UNIX)
	set(whole_archive_start "-Wl,--whole-archive")
	set(whole_archive_end "-Wl,--no-whole-archive")
endif()

target_link_libraries(core3
	${whole_archive_start}
	db3 conf3 web3 status3 ping3 login3 chat3 core3terrain core3templates core3pathfinding idlobjects
	${whole_archive_end}
	${ENGINE3_LIBRARIES}
	${ZLIB_LIBRARIES} Threads::Threads ${MYSQL_CLIENT_LIBS} ${LUA_LIBRARIES} ${DB_LIBRARIES} ${CMAKE_DL_LIBS} ${OPENSSL_LIBRARIES} gmock)

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