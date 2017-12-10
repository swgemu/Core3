# Copyright 2010, Dimitri Kaparis <kaparis.dimitri at gmail dot com>

# CMake module to find Berkeley DB

# For MSVC, only static libraries are used (with 's' suffix)

# This module uses:
#
# DB_ROOT_DIR - set to BerkeleyDB's root directory
# DB_VERSION - set to required BerkeleyDB version, e.g. 47

#set(DB_ROOT_DIR /usr/local/BerkeleyDB.5.3)
set(DB_VERSION 5.3)

# This module defines:
# DB_FOUND - True if BerkleyDB is found
# DB_INCLUDE_DIR - BerkeleyDB's include directory
# DB_LIBRARIES - Libraries needed to use Berkeley DB

#find_path(DB_INCLUDE_DIR db.h db_cxx.h
#          PATHS ${DB_ROOT_DIR}
#          PATH_SUFFIXES include
#          )
          
#set(DB_INCLUDE_DIR /usr/local/BerkeleyDB.5.3/include)
#set(DB_LIBRARIES /usr/local/BerkeleyDB.5.3/lib)

#include(FindPackageHandleStandardArgs)
#find_package_handle_standard_args(DB DEFAULT_MSG DB_INCLUDE_DIR DB_LIBRARIES)


set(DB_VERSION 5.3)

IF (DB_INCLUDE_DIR)
    # Already in cache, be silent
    SET(DB_FIND_QUIETLY TRUE)
ENDIF (DB_INCLUDE_DIR)

FIND_PATH(DB_INCLUDE_DIR db.h
        /opt/local/include/db53/
        /usr/local/BerkeleyDB.5.3/include
        /usr/include/
        NO_DEFAULT_PATH
        )

FIND_LIBRARY(DB_LIBRARIES
        NAMES db-5.3
        PATHS /opt/local/lib/db53 /usr/local/BerkeleyDB.5.3/lib /usr/lib/x86_64-linux-gnu/
        )

IF (DB_INCLUDE_DIR AND DB_LIBRARIES)
    SET(DB_FOUND TRUE)
ELSE ()
    SET(DB_FOUND FALSE)
    SET(DB_LIBRARIES)
    SET(DB_INCLUDE_DIR)
ENDIF ()

IF (DB_FOUND)
    IF (NOT DB_FIND_QUIETLY)
        MESSAGE(STATUS "Found berkeley db includes: ${DB_INCLUDE_DIR}")
        MESSAGE(STATUS "Found berkeley db library: ${DB_LIBRARIES}")
    ENDIF (NOT DB_FIND_QUIETLY)
ELSE (DB_FOUND)
    IF (DB_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could NOT find berkeley db 5.3 library")
    ENDIF (DB_FIND_REQUIRED)
ENDIF (DB_FOUND)

MARK_AS_ADVANCED(
        DB_LIBRARIES
        DB_INCLUDE_DIR
)
