# Copyright 2010, Dimitri Kaparis <kaparis.dimitri at gmail dot com>

# CMake module to find Berkeley DB

# For MSVC, only static libraries are used (with 's' suffix)

# This module uses:
#
# DB_ROOT_DIR - set to BerkeleyDB's root directory
# DB_VERSION - set to required BerkeleyDB version, e.g. 47

set(DB_ROOT_DIR /usr/local/BerkeleyDB.5.0)
#set(DB_VERSION 5.0)

# This module defines:
# DB_FOUND - True if BerkleyDB is found
# DB_INCLUDE_DIR - BerkeleyDB's include directory
# DB_LIBRARIES - Libraries needed to use Berkeley DB

#find_path(DB_INCLUDE_DIR db.h db_cxx.h
 #         PATHS ${DB_ROOT_DIR}
  #        PATH_SUFFIXES include
   #       )
          
set(DB_INCLUDE_DIR /usr/local/BerkeleyDB.5.0/include)
set(DB_LIBRARIES /usr/local/BerkeleyDB.5.0/lib)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(DB DEFAULT_MSG DB_INCLUDE_DIR DB_LIBRARIES)