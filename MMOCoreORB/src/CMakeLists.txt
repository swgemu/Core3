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

file(GLOB_RECURSE odb_internals "pathfinding/*.cpp" "server/chat/*.cpp" "server/db/*.cpp"
	"server/login/*.cpp" "server/web/*.cpp"  "server/web/*.c" "server/ping/*.cpp" "templates/*.cpp"
	"server/status/*.cpp" "terrain/*.cpp" "conf/*.cpp")
file(GLOB_RECURSE odb_internals_h "server/web/*.h")

if(ENABLE_ODB)
	file(GLOB_RECURSE odb3_sources "odb/*.cpp")
	file(GLOB_RECURSE odb3_headers "odb/*.h")
endif(ENABLE_ODB)

file(GLOB_RECURSE tests_sources "tests/*.cpp")
file(GLOB_RECURSE tests_headers "tests/*.h")

set(core3tests_libs)
set(gmock_libs)

add_dependencies(idlobjects engine3)

if(COMPILE_TESTS)
	# Define tests
	enable_testing()

	set(core3tests_libs ${tests_headers} ${tests_sources})
	set(gmock_libs gmock)
endif(COMPILE_TESTS)

# Create core3 binary
add_executable(core3 main.cpp server/ServerCore.cpp ${core3tests_libs} ${tre3_sources} ${tre3_headers} ${zone3_sources} ${zone3_headers})

if(ENABLE_ODB)
	add_executable(odb3 server/ServerCore.cpp ${odb3_sources} ${odb3_headers} ${autogen_sources} ${autogen_headers} ${zone3_sources} ${zone3_headers}
		${tre3_sources} ${tre3_headers} ${odb_internals} ${odb_internals_h} ${tests_sources})
	target_compile_definitions(odb3 PUBLIC -DODB_SERIALIZATION)
endif(ENABLE_ODB)

if(COMPILE_TESTS)
	add_dependencies(core3 idlobjects)
else(COMPILE_TESTS)
	add_dependencies(core3 idlobjects)
endif(COMPILE_TESTS)

add_dependencies(core3 engine3)

if(ENABLE_ODB)
	add_dependencies(odb3 engine3 idlobjects)
endif(ENABLE_ODB)

set(whole_archive_start)
set(whole_archive_end)

# Add custom link options
if(WIN32)
	set(whole_archive_start "")
	set(whole_archive_end "")

	set (CMAKE_LINK_WHAT_YOU_USE OFF) 
elseif(APPLE)
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
	engine3
	${gmock_libs}
	${Boost_LIBRARIES}
	${GCCLIBATOMIC_LIBRARY} ${PTHREAD_LIB_LINK} ${MYSQL_LIB}
	${LUA_LIBRARIES}
	${DB_LIBRARIES} ${OPENSSL_LIBRARIES}
	${ZLIB_LIBRARIES} ${CMAKE_DL_LIBS})

if (NOT ENABLE_ASAN AND NOT ENABLE_TSAN AND NOT ENABLE_UBSAN AND JEMALLOC_FOUND AND ENABLE_JEMALLOC_LINK)
	target_link_libraries(core3 ${JEMALLOC_LIBRARIES})
endif()

if(ENABLE_MULTITHREADED_LINKER)
	use_gold(core3)
endif(ENABLE_MULTITHREADED_LINKER)

if(ENABLE_ODB)
	target_link_libraries(odb3
		engine3
		${gmock_libs} ${Boost_LIBRARIES}
		${GCCLIBATOMIC_LIBRARY} ${PTHREAD_LIB_LINK}
		${MYSQL_LIB} ${LUA_LIBRARIES}
		${DB_LIBRARIES} ${OPENSSL_LIBRARIES}
		${ZLIB_LIBRARIES} ${CMAKE_DL_LIBS})

if (NOT ENABLE_ASAN AND NOT ENABLE_TSAN AND NOT ENABLE_UBSAN AND JEMALLOC_FOUND AND ENABLE_JEMALLOC_LINK)
	target_link_libraries(odb3 ${JEMALLOC_LIBRARIES})
endif()

if(ENABLE_MULTITHREADED_LINKER)
	use_gold(odb3)
endif(ENABLE_MULTITHREADED_LINKER)

# Copy core3 binary
add_custom_command(
	TARGET odb3 POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	$<TARGET_FILE:odb3>
	${CMAKE_SOURCE_DIR}/bin/)

endif(ENABLE_ODB)
# Copy core3 binary
add_custom_command(
	TARGET core3 POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	$<TARGET_FILE:core3>
	${CMAKE_SOURCE_DIR}/bin/)

if(GIT_FOUND AND RUN_GIT)
    add_custom_command(
        TARGET core3 POST_BUILD
        COMMAND ${GIT_EXECUTABLE} log --no-merges --pretty=format:"%h was %an, %ar, message: %s" -10 > ${CMAKE_SOURCE_DIR}/bin/conf/rev.txt
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		VERBATIM)
endif()

if(COMPILE_TESTS)
	add_test(core3
		COMMAND $<TARGET_FILE:core3> runUnitTests
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)
endif(COMPILE_TESTS)

add_custom_target(idl
	COMMAND ${Java_JAVA_EXECUTABLE} ${IDLC_JAVA_ARGS} ${IDL_DIRECTIVES} -sd src anyadEclipse
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Building idl sources"
        VERBATIM)

add_custom_target(rebuild-idl
	COMMAND ${Java_JAVA_EXECUTABLE} ${IDLC_JAVA_ARGS} ${IDL_DIRECTIVES} -rb -sd src anyadEclipse
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	COMMENT "Rebuilding idl sources"
        VERBATIM)

if (ENABLE_REST_SERVER OR ENABLE_SESSION_API)
	find_package(cpprestsdk QUIET NAMES cpprestsdk cpprest)

	if (cpprestsdk_FOUND)
		target_link_libraries(core3 cpprestsdk::cpprest)

		if(ENABLE_ODB)
			target_link_libraries(odb3 cpprestsdk::cpprest)
		endif()

		message(STATUS "Compiling with cpprestsdk package")
	else ()
		find_path(CUST_CPPREST_INCLUDE_DIR
			NAMES
			cpprest/http_listener.h
			PATHS
			${CASABLANCA_PKGCONF_INCLUDE_DIRS}
			${CASABLANCA_DIR}
			$ENV{CASABLANCA_DIR}
			/usr/local/include
			/usr/include
			../../casablanca
			PATH_SUFFIXES
			Release/include
			include
			)

		if (CUST_CPPREST_INCLUDE_DIR-NOTFOUND)
			message(STATUS "Cant find cpprest/http_listener.h")
		endif(CUST_CPPREST_INCLUDE_DIR-NOTFOUND)

		# Library
		find_library(CUST_CPPREST_LIBRARY
			NAMES
			cpprest
			cpprest_2_9.lib
			cpprestsdk
			PATHS
			${CASABLANCA_PKGCONF_LIBRARY_DIRS}
			${CASABLANCA_DIR}
			${CASABLANCA_DIR}
			$ENV{CASABLANCA_DIR}
			/usr/local
			/usr/lib
			/usr/local/lib
			/usr
			../../casablanca
			PATH_SUFFIXES
			lib
			Release/build.release/Binaries/
			build.release/Binaries/
			)

		if (CUST_CPPREST_LIBRARY-NOTFOUND)
			message(STATUS "Cant find cpprestsdk library")
		endif(CUST_CPPREST_LIBRARY-NOTFOUND)

		if (CUST_CPPREST_INCLUDE_DIR-NOTFOUND AND CUST_CPPREST_LIBRARY-NOTFOUND)
			message(STATUS "cpprestsdk not found, compiling without")
		else ()
			include_directories(${CUST_CPPREST_INCLUDE_DIR})
			target_link_libraries(core3 ${CUST_CPPREST_LIBRARY})

			if(ENABLE_ODB)
				target_link_libraries(odb3 ${CUST_CPPREST_LIBRARY})
			endif()

			message(STATUS "Compiling with cpprestsdk")
		endif()
	endif()
endif()
