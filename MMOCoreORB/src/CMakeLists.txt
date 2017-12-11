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

if(BUILD_IDL)
	file(GLOB_RECURSE idls "${CMAKE_SOURCE_DIR}/src/*.idl")

	set(autogen_sources)
	set(autogen_headers)
	foreach(idl ${idls})
		string(REPLACE "src/" "src/autogen/" autogen_base ${idl})
		string(REPLACE ".idl" ".cpp" autogen_cpp ${autogen_base})
		string(REPLACE ".idl" ".h" autogen_h ${autogen_base})
		set(autogen_sources ${autogen_sources} "${autogen_cpp}")
		set(autogen_headers ${autogen_headers} "${autogen_h}")

		string(REGEX REPLACE ".+\/src\/" "" idl_f ${idl})
		string(CONCAT idl_b "src/" ${idl_f})

		get_filename_component(idl_we ${idl} NAME_WE)

		add_custom_command(OUTPUT "${autogen_cpp}" "${autogen_h}"
			COMMAND ${Java_JAVA_EXECUTABLE} -Xmx64M -cp ${IDLC_BIN_DIR}/idlc.jar org.sr.idlc.compiler.Compiler ${IDL_DIRECTIVES} -silence -rebuild -sd src ${idl_f}
			WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
			DEPENDS ${idl}
			COMMENT "Building IDL object ${idl_b}"
			VERBATIM)
	endforeach()

	set_source_files_properties(${${autogen_sources}} ${${autogen_headers}} PROPERTIES GENERATED TRUE)

	add_library(idlobjects STATIC ${autogen_sources} ${autogen_headers})
else(BUILD_IDL)
	file(GLOB_RECURSE autogen_sources "autogen/*.cpp")
	file(GLOB_RECURSE autogen_headers "autogen/*.h")

	add_library(idlobjects STATIC ${autogen_sources} ${autogen_headers})
endif()

set_target_properties(idlobjects PROPERTIES LINKER_LANGUAGE CXX)

# Create core3 binary
add_executable(core3 server/ServerCore.cpp tre3/TreeFile.cpp main.cpp)
add_dependencies(core3 zone3)

# Add libraries
if(APPLE)
    target_link_libraries(core3
            -Wl,-all_load
            db3 conf3 web3 status3 ping3 login3 zone3 chat3 core3terrain core3templates core3pathfinding idlobjects
            -Wl,-noall_load
            ${ENGINE3_LIBRARIES}
            ${ZLIB_LIBRARIES} Threads::Threads ${MYSQL_CLIENT_LIBS} ${LUA_LIBRARIES} ${DB_LIBRARIES} ${CMAKE_DL_LIBS} ${OPENSSL_LIBRARIES} gtest)
elseif(UNIX)
    target_link_libraries(core3
        	-Wl,--whole-archive
        	db3 conf3 web3 status3 ping3 login3 zone3 chat3 core3terrain core3templates core3pathfinding idlobjects
        	-Wl,--no-whole-archive
        	${ENGINE3_LIBRARIES}
        	${ZLIB_LIBRARIES} Threads::Threads ${MYSQL_CLIENT_LIBS} ${LUA_LIBRARIES} ${DB_LIBRARIES} ${CMAKE_DL_LIBS} ${OPENSSL_LIBRARIES} gtest)
endif()

# Install core3 binary
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/core3 DESTINATION bin)

