# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(core3 CXX C)

include(CheckCXXSourceCompiles)
include(CheckCXXCompilerFlag)

# Set cpp requirements
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (CMAKE_COMPILER_IS_GNUCC AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.4)
	message(FATAL_ERROR "Only GCC 5.4 or greater is supported")
endif()

# Set up options
option(BUILD_IDL "Generate idl c++ sources with cmake" ON)
option(IDL_NOPRELOCKS "Disables all prelock annotations" OFF)
option(ENABLE_CCACHE "Enables ccache search and usage" ON)
option(RUN_GIT "Runs git log to dump last commit messages into rev.txt" OFF)
option(COMPILE_TESTS "Enables mock generation in idlc and test compiling" ON)
option(LOGIN_SERVER_EXTRA_PORTS "Enables login server with extra ports config" OFF)
option(ENABLE_ASAN "Enables address sanitizer compiling" OFF)
option(ENABLE_TSAN "Enables thread sanitizer compiling" OFF)
option(ENABLE_UBSAN "Enables undefined behavior sanitizer compiling" OFF)
option(ENABLE_NATIVE "Enables -march=native compiler option" ON)

# Set cmake paths
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Add lua includes and libraries
find_package(Lua "5.3" REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

# Find mysql includes and libraries
find_package(MySql REQUIRED)
#include_directories(${MYSQL_INCLUDE_DIR}) already included in find

# Find berkeley includes and libraries
find_package(Berkeley REQUIRED)
include_directories(${DB_INCLUDE_DIR})

find_package(Java 1.5 COMPONENTS Runtime REQUIRED )

# Find engine3 includes and libraries
find_package(Engine3 REQUIRED)
include_directories(${ENGINE3_INCLUDE_DIR})

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

find_package(ZLIB REQUIRED)
include_directories(${ZLIB_INCLUDE_DIRS})

# Find and set -pthreads
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost QUIET OPTIONAL_COMPONENTS thread)

function(check_working_cxx_atomics varname)
	set(OLD_CMAKE_REQUIRED_FLAGS ${CMAKE_REQUIRED_FLAGS})
	set(CMAKE_REQUIRED_FLAGS "-std=c++11")
	CHECK_CXX_SOURCE_COMPILES("
	#include <atomic>
	struct test_type { float x[3]; };
	std::atomic<test_type> atom;
	test_type old;
	test_type newval;
	int main() {
	newval.x[2] = 3;
	return atom.compare_exchange_strong(old, newval);
	}
	" ${varname})
	set(CMAKE_REQUIRED_FLAGS ${OLD_CMAKE_REQUIRED_FLAGS})
endfunction(check_working_cxx_atomics)

check_working_cxx_atomics(HAVE_CXX_ATOMICS_WITHOUT_LIB)

if (NOT HAVE_CXX_ATOMICS_WITHOUT_LIB)
	find_package(GccAtomic REQUIRED)
endif()

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

find_package(Git QUIET)

if(ENABLE_CCACHE)
    find_program(CCACHE_FOUND ccache)

    if(CCACHE_FOUND)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)

	message(STATUS "Using ccache")
    endif(CCACHE_FOUND)
endif(ENABLE_CCACHE)

if(IDL_NOPRELOCKS)
    set(IDL_DIRECTIVES ${IDL_DIRECTIVES} -noprelocks)
endif(IDL_NOPRELOCKS)

# Include googlemock and googletest
if(COMPILE_TESTS)
    add_subdirectory(utils/googletest-release-1.8.0/googlemock)

    include_directories(${CMAKE_SOURCE_DIR}/utils/googletest-release-1.8.0/googletest/include)
    include_directories(${CMAKE_SOURCE_DIR}/utils/googletest-release-1.8.0/googlemock/include)

    add_definitions(-DCOMPILE_CORE3_TESTS)
else(COMPILE_TESTS)
    set(IDL_DIRECTIVES ${IDL_DIRECTIVES} -nomocks)
endif(COMPILE_TESTS)

if (LOGIN_SERVER_EXTRA_PORTS)
    add_definitions(-DUSE_RANDOM_EXTRA_PORTS)
endif(LOGIN_SERVER_EXTRA_PORTS)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/autogen)
include_directories(${CMAKE_SOURCE_DIR}/utils)

# Define global build gcc compatible flags
set(GCCEXTRAFLAGS "-Wall -Wextra -Wno-unused -Wno-sign-compare -Wno-multichar -Wno-unused-parameter -Wno-overloaded-virtual -Wno-missing-declarations -Werror")

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${GCCEXTRAFLAGS})

    CHECK_CXX_COMPILER_FLAG(-Wno-return-std-move HAVE_NO_STD_MOVE_RETURN)

    if (HAVE_NO_STD_MOVE_RETURN)
	    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-return-std-move")
    endif(HAVE_NO_STD_MOVE_RETURN)

    if (ENABLE_ASAN)
	   set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
	   set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} -fsanitize=address")
	   message(STATUS "Adress sanitizer enabled")
    endif(ENABLE_ASAN)

    if (ENABLE_TSAN)
	   set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
	   set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} -fsanitize=thread")
	   message(STATUS "Thread sanitizer enabled")
    endif(ENABLE_TSAN)

    if (ENABLE_UBSAN)
	    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
	    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} -fsanitize=undefined")
	    message(STATUS "Undefined behavior sanitizer sanitizer enabled")
    endif(ENABLE_UBSAN)

    if (ENABLE_NATIVE)
	   set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
    endif(ENABLE_NATIVE)

    if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
	   set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
    endif()
endif()

add_definitions(-DDEFAULT_DYNAMIC_CAST)

add_subdirectory(src)
add_subdirectory(src/conf)
add_subdirectory(src/terrain)
add_subdirectory(src/templates)
add_subdirectory(src/pathfinding)
add_subdirectory(src/server/db)
add_subdirectory(src/server/status)
add_subdirectory(src/server/web)
add_subdirectory(src/server/ping)
add_subdirectory(src/server/login)
add_subdirectory(src/server/chat)
add_subdirectory(src/client)

set_source_files_properties(tags PROPERTIES GENERATED true)
add_custom_target(tags
	COMMAND ctags -R --fields=+iaS --extra=+q src/
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

set_source_files_properties(compile_commands.json PROPERTIES GENERATED true)
add_custom_target(compdb
	COMMAND compdb -p ${CMAKE_BINARY_DIR} list > compile_commands.json
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
