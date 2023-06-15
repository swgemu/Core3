# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.

cmake_minimum_required(VERSION 3.7.0 FATAL_ERROR)

find_program(CLANGXX_EXECUTABLE_PATH NAMES clang++)

if (CLANGXX_EXECUTABLE_PATH)
	find_program(CMAKE_C_COMPILER clang)
	find_program(CMAKE_CXX_COMPILER clang++)
	message(STATUS "Found ${CMAKE_CXX_COMPILER} using clang compiler.")
endif()

project(core3 CXX C)

# Set cpp requirements
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CheckCXXSourceCompiles)
include(CheckCXXCompilerFlag)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.4)
	message(FATAL_ERROR "GCC version must be at least 5.4!")
    endif()
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 16)
        message(FATAL_ERROR "Clang version must be at least 16!")
    endif()
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.10)
        message(FATAL_ERROR "Visual Studio version must be at least 2017!")
    endif()
else()
    message(WARNING "You are using an unsupported compiler! Compilation has only been tested with Clang, GCC and Visual Studio 2019.")
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(FATAL_ERROR "32 bit compile targets are not supported")
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
option(ENABLE_OMIT_FRAMEPOINTER "Enables -fno-omit-frame-pointer compiler option" ON)
option(ENABLE_ERROR_ON_WARNINGS "Enables -Werror compiler option" ON)
option(ENABLE_REST_SERVER "Enables REST API Server" OFF)
option(ENABLE_SESSION_API "Enables Session API support" OFF)
option(ENABLE_ODB "Enables odb3 compiling" OFF)
option(ENABLE_ODB_REFERENCES "Sets ODB_REFERENCES define" ON) #needs to match engine3
option(ENABLE_BUILD_CLIENT "Enables core3client build" ON)
option(ENABLE_JEMALLOC_LINK "Enables jemalloc linking if found" ON)
option(ENABLE_MULTITHREADED_LINKER "Enables ld.gold/lld with --threads check and use" OFF)
option(ENABLE_LOCKFREE_BCLIENT_BUFFERS "Enables lock free base client buffers, requires boost thread" OFF) #needs to match engine3
option(DUMP_ALL_CMAKE_VARIABLES "Prints all cmake variables" OFF)

# Set cmake paths
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

include(UseGold)

find_package(Git QUIET)

# Add lua includes and libraries
find_package(Lua "5.3" EXACT REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

# Find mysql includes and libraries
find_package(MySql REQUIRED)
#include_directories(${MYSQL_INCLUDE_DIR}) already included in find

# Find berkeley includes and libraries
find_package(Berkeley REQUIRED)
include_directories(${DB_INCLUDE_DIR})

find_package(Java 1.5 COMPONENTS Runtime REQUIRED)

# Find engine3 includes and libraries
find_package(Engine3 REQUIRED)
include_directories(${ENGINE3_INCLUDE_DIR})

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

find_package(ZLIB REQUIRED)
include_directories(${ZLIB_INCLUDE_DIRS})

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	message(STATUS "Compiling with AI debug enabled")
	add_definitions(-DDEBUG_AI)
endif()

if (ENABLE_SESSION_API)
    message(STATUS "Compiling with session API support")
    add_definitions(-DWITH_SESSION_API)
endif()

if (ENABLE_REST_SERVER)
	message(STATUS "Compiling with REST API support")
	add_definitions(-DWITH_REST_API)
endif(ENABLE_REST_SERVER)

if(ENABLE_MULTITHREADED_LINKER)
	macro(check_cxx_linker_flag _Flag _Var)
		set(old_link_libs "${CMAKE_REQUIRED_LIBRARIES}")
		set(CMAKE_REQUIRED_LIBRARIES ${old_link_libs} "${_Flag}")
		check_cxx_compiler_flag("${_Flag}" ${_Var})
		set(CMAKE_REQUIRED_LIBRARIES "${old_link_libs}")
	endmacro()

	check_cxx_linker_flag("-fuse-ld=lld" LLD_LINKER_SUPPORTED)
	check_cxx_linker_flag("-fuse-ld=gold" GOLD_LINKER_SUPPORTED)
	check_cxx_compiler_flag("-Wl,-z,defs" WL_ZDEFS_SUPPORTED)

	if(LLD_LINKER_SUPPORTED)
		set(LINKER_IS_LLD 1 CACHE INTERNAL "use lld linker")
		message(STATUS "Using lld linker")
	elseif(GOLD_LINKER_SUPPORTED)
		set(LINKER_IS_GOLD 1 CACHE INTERNAL "use gold linker")
		message(STATUS "Using gold linker")
	else()
		message(STATUS "ENABLE_MULTITHREADED_LINKER failed to find linker.")
	endif()

	if(LINKER_IS_GOLD)
		check_cxx_linker_flag("-fuse-ld=gold -Wl,--threads -Wl,--thread-count,2" LINKER_THREADS_SUPPORTED)
		check_cxx_linker_flag("-fuse-ld=gold -Wl,--gdb-index" GDB_INDEX_SUPPORTED)
	elseif(LINKER_IS_LLD)
		check_cxx_linker_flag("-fuse-ld=lld -Wl,--threads" LINKER_THREADS_SUPPORTED)
		check_cxx_linker_flag("-fuse-ld=lld -Wl,--gdb-index" GDB_INDEX_SUPPORTED)
	endif()
endif(ENABLE_MULTITHREADED_LINKER)

# Find and set -pthreads
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

if(WIN32)
	string(TOLOWER ${CMAKE_BUILD_TYPE} E3_BUILD_TYPE)

	if(E3_BUILD_TYPE STREQUAL "debug")
		set(PTHREAD_LIB_LINK pthreadVCE3d)
	else()
		set(PTHREAD_LIB_LINK pthreadVCE3)
	endif()
else()
	set(PTHREAD_LIB_LINK Threads::Threads)
endif()

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(JEMALLOC QUIET)

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
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    add_subdirectory(utils/googletest-release-1.13.0)

    include_directories(${CMAKE_SOURCE_DIR}/utils/googletest-release-1.13.0/googletest/include)
    include_directories(${CMAKE_SOURCE_DIR}/utils/googletest-release-1.13.0/googlemock/include)

	enable_testing()

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

if (ENABLE_ODB_REFERENCES)
	add_definitions(-DODB_REFERENCES)
endif()

if (ENABLE_LOCKFREE_BCLIENT_BUFFERS)
	add_definitions(-DLOCKFREE_BCLIENT_BUFFERS)
endif()

find_package(Boost REQUIRED COMPONENTS thread)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Define global build gcc compatible flags to check and add if available
    set(GCCEXTRAFLAGS -Wall
	-Wextra
	-Wno-unused
	-Wno-sign-compare
	-Wno-multichar
	-Wno-unused-parameter
	-Wno-overloaded-virtual
	-Wno-missing-declarations
	-Wno-return-std-move
	-Wno-implicit-fallthrough
	-Wno-class-memaccess
	-fcolor-diagnostics)

    foreach(flag_comp ${GCCEXTRAFLAGS})
	CHECK_CXX_COMPILER_FLAG(${flag_comp} CxxFlag${flag_comp})

	if (CxxFlag${flag_comp})
		set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag_comp}")
	endif()
    endforeach(flag_comp)

    if (ENABLE_ERROR_ON_WARNINGS)
	   set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
    endif(ENABLE_ERROR_ON_WARNINGS)

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
	   CHECK_CXX_COMPILER_FLAG(-march=native CxxFlagMnative)

	   if (CxxFlagMnative)
	        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
	   endif (CxxFlagMnative)
    endif(ENABLE_NATIVE)

    if (ENABLE_OMIT_FRAMEPOINTER)
	   CHECK_CXX_COMPILER_FLAG(-fno-omit-frame-pointer CxxFlagFramePointer)

	   if (CxxFlagFramePointer)
           	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
	   endif (CxxFlagFramePointer)
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

if (ENABLE_BUILD_CLIENT)
	add_subdirectory(src/client)
endif()

set_source_files_properties(tags PROPERTIES GENERATED true)
add_custom_target(tags
	COMMAND ctags -R --fields=+iaS --extra=+q src/
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

set_source_files_properties(compile_commands.json PROPERTIES GENERATED true)
add_custom_target(compdb
	COMMAND compdb -p ${CMAKE_BINARY_DIR} list > compile_commands.json
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_custom_target(update-engine3
	COMMAND ${GIT_EXECUTABLE} submodule update --recursive --remote
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

set_property(TARGET core3 PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

message(STATUS "Build type: " ${CMAKE_BUILD_TYPE})
#message(STATUS "Compiler flags:" ${CMAKE_CXX_COMPILE_FLAGS})

if (${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
	message(STATUS "Compiler cxx release with debug flags: " ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
elseif (${CMAKE_BUILD_TYPE} STREQUAL "Release")
	message(STATUS "Compiler cxx release flags: " ${CMAKE_CXX_FLAGS_RELEASE})
elseif (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	message(STATUS "Compiler cxx debug flags: " ${CMAKE_CXX_FLAGS_DEBUG})
endif ()
#message(STATUS "Compiler cxx min size flags:" ${CMAKE_CXX_FLAGS_MINSIZEREL})
message(STATUS "Compiler extra cxx flags:" ${CMAKE_CXX_FLAGS})
message(STATUS "Available targets: tags compdb update-engine3 core3 odb3 idl rebuild-idl")

if (DUMP_ALL_CMAKE_VARIABLES)
	get_cmake_property(_variableNames VARIABLES)

	foreach (_variableName ${_variableNames})
	    message(STATUS "${_variableName}=${${_variableName}}")
	endforeach()
endif()
