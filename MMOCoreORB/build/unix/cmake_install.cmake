# Install script for directory: /home/oru/git/Core3/MMOCoreORB

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/home/oru/git/Core3/MMOCoreORB")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/oru/git/Core3/MMOCoreORB/build/unix/src/cmake_install.cmake")
  INCLUDE("/home/oru/git/Core3/MMOCoreORB/build/unix/src/server/conf/cmake_install.cmake")
  INCLUDE("/home/oru/git/Core3/MMOCoreORB/build/unix/src/server/db/cmake_install.cmake")
  INCLUDE("/home/oru/git/Core3/MMOCoreORB/build/unix/src/server/status/cmake_install.cmake")
  INCLUDE("/home/oru/git/Core3/MMOCoreORB/build/unix/src/server/web/cmake_install.cmake")
  INCLUDE("/home/oru/git/Core3/MMOCoreORB/build/unix/src/server/ping/cmake_install.cmake")
  INCLUDE("/home/oru/git/Core3/MMOCoreORB/build/unix/src/server/login/cmake_install.cmake")
  INCLUDE("/home/oru/git/Core3/MMOCoreORB/build/unix/src/server/zone/cmake_install.cmake")
  INCLUDE("/home/oru/git/Core3/MMOCoreORB/build/unix/src/server/chat/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/home/oru/git/Core3/MMOCoreORB/build/unix/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/home/oru/git/Core3/MMOCoreORB/build/unix/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
