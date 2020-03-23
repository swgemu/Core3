# Install script for directory: /home/vagrant/workspace/Core3/MMOCoreORB

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/vagrant/workspace/Core3/MMOCoreORB/build/unix/ninja-debug/utils/engine3/MMOEngine/cmake_install.cmake")
  include("/home/vagrant/workspace/Core3/MMOCoreORB/build/unix/ninja-debug/utils/googletest-release-1.10.0/cmake_install.cmake")
  include("/home/vagrant/workspace/Core3/MMOCoreORB/build/unix/ninja-debug/src/cmake_install.cmake")
  include("/home/vagrant/workspace/Core3/MMOCoreORB/build/unix/ninja-debug/src/conf/cmake_install.cmake")
  include("/home/vagrant/workspace/Core3/MMOCoreORB/build/unix/ninja-debug/src/terrain/cmake_install.cmake")
  include("/home/vagrant/workspace/Core3/MMOCoreORB/build/unix/ninja-debug/src/templates/cmake_install.cmake")
  include("/home/vagrant/workspace/Core3/MMOCoreORB/build/unix/ninja-debug/src/pathfinding/cmake_install.cmake")
  include("/home/vagrant/workspace/Core3/MMOCoreORB/build/unix/ninja-debug/src/server/db/cmake_install.cmake")
  include("/home/vagrant/workspace/Core3/MMOCoreORB/build/unix/ninja-debug/src/server/status/cmake_install.cmake")
  include("/home/vagrant/workspace/Core3/MMOCoreORB/build/unix/ninja-debug/src/server/web/cmake_install.cmake")
  include("/home/vagrant/workspace/Core3/MMOCoreORB/build/unix/ninja-debug/src/server/ping/cmake_install.cmake")
  include("/home/vagrant/workspace/Core3/MMOCoreORB/build/unix/ninja-debug/src/server/login/cmake_install.cmake")
  include("/home/vagrant/workspace/Core3/MMOCoreORB/build/unix/ninja-debug/src/server/chat/cmake_install.cmake")
  include("/home/vagrant/workspace/Core3/MMOCoreORB/build/unix/ninja-debug/src/client/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/vagrant/workspace/Core3/MMOCoreORB/build/unix/ninja-debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
