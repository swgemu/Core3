# CMake module to find Berkeley DB

# This module uses:
#
# DB_VERSION - set to required BerkeleyDB version, e.g. 47

# This module defines:
# DB_FOUND - True if BerkleyDB is found
# DB_INCLUDE_DIR - BerkeleyDB's include directory
# DB_LIBRARIES - Libraries needed to use Berkeley DB

set(DB_VERSION 5.3)

IF (DB_INCLUDE_DIR)
    SET(DB_FIND_QUIETLY_INCLUDE TRUE)
ENDIF (DB_INCLUDE_DIR)

IF (DB_LIBRARIES)
    SET(DB_FIND_QUIETLY_LIB TRUE)
ENDIF (DB_LIBRARIES)

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
    if(DB_INCLUDE_DIR)
        file( STRINGS "${DB_INCLUDE_DIR}/db.h"
                DB_H REGEX "^#define[ \t]+DB_VERSION_STRING[ \t]+\"[^\"]+\".*$" )
        string( REGEX REPLACE
                "^.*DB_VERSION_STRING[ \t]+\"([^\"]+)\".*$" "\\1" DB_VERSION_STRING
                "${DB_H}" )
    endif()

    IF (NOT DB_FIND_QUIETLY_INCLUDE)
        if(DB_VERSION_STRING)
            MESSAGE(STATUS "Found berkeley db version: ${DB_VERSION_STRING}")
        endif()

        MESSAGE(STATUS "Found berkeley db includes: ${DB_INCLUDE_DIR}")
    ENDIF (NOT DB_FIND_QUIETLY_INCLUDE)

    IF (NOT DB_FIND_QUIETLY_LIB)
        MESSAGE(STATUS "Found berkeley db library: ${DB_LIBRARIES}")
    ENDIF (NOT DB_FIND_QUIETLY_LIB)
ELSE (DB_FOUND)
    IF (Berkeley_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could NOT find berkeley db 5.3 library")
    ENDIF (Berkeley_FIND_REQUIRED)
ENDIF (DB_FOUND)

MARK_AS_ADVANCED(
        DB_LIBRARIES
        DB_INCLUDE_DIR
)
