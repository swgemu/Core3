# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

# Add web sources
file(GLOB_RECURSE web3_sources "*.cpp")
file(GLOB_RECURSE web3_headers "*.h")

# Add web includes
include_directories(../..)

add_library(web3 STATIC ${web3_sources} ${web3_headers})

if (ENABLE_REST_SERVER)
	message(STATUS "REST Server enabled")

	if (cpprestsdk_FOUND)
		target_link_libraries(web3 PRIVATE cpprestsdk::cpprest)

		add_definitions(-DCOMPILE_CORE3_REST)

		message(STATUS "Compiling REST Server with cpprestsdk package")
	else ()
		if (CUST_CPPREST_INCLUDE_DIR-NOTFOUND AND CUST_CPPREST_LIBRARY-NOTFOUND)
			message(STATUS "Can't compile REST Server, cpprestsdk not found.")
		else ()
			include_directories(${CUST_CPPREST_INCLUDE_DIR})
			target_link_libraries(web3 PRIVATE ${CUST_CPPREST_LIBRARY})

			add_definitions(-DCOMPILE_CORE3_REST)

			message(STATUS "Compiling REST Server with cpprestsdk")
		endif()
	endif()
endif()

add_dependencies(web3 idlobjects)
