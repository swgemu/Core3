# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

# Add web sources
file(GLOB_RECURSE web3_sources "*.cpp")
file(GLOB_RECURSE web3_headers "*.h")

# Add web includes
include_directories(../..)

add_library(web3 STATIC ${web3_sources} ${web3_headers} mongoose/mongoose.c)

if (ENABLE_REST_SERVER)
	find_package(cpprestsdk QUIET NAMES cpprestsdk cpprest)

	if (cpprestsdk_FOUND)
		target_link_libraries(web3 PRIVATE cpprestsdk::cpprest)

		add_definitions(-DCOMPILE_CORE3_REST)

		message(STATUS "Compiling with cpprestsdk")
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
			target_link_libraries(web3 PRIVATE ${CUST_CPPREST_LIBRARY})

			add_definitions(-DCOMPILE_CORE3_REST)

			message(STATUS "Compiling with cpprestsdk")
		endif()
	endif()
endif()

add_dependencies(web3 idlobjects)

