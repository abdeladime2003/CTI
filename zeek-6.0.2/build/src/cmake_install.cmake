# Install script for directory: /home/abdo/Cti_Project/zeek-6.0.2/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local/zeek")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdo/Cti_Project/zeek-6.0.2/build/src/analyzer/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdo/Cti_Project/zeek-6.0.2/build/src/packet_analysis/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdo/Cti_Project/zeek-6.0.2/build/src/broker/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdo/Cti_Project/zeek-6.0.2/build/src/telemetry/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdo/Cti_Project/zeek-6.0.2/build/src/zeekygen/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdo/Cti_Project/zeek-6.0.2/build/src/file_analysis/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdo/Cti_Project/zeek-6.0.2/build/src/input/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdo/Cti_Project/zeek-6.0.2/build/src/iosource/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdo/Cti_Project/zeek-6.0.2/build/src/logging/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdo/Cti_Project/zeek-6.0.2/build/src/probabilistic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdo/Cti_Project/zeek-6.0.2/build/src/session/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdo/Cti_Project/zeek-6.0.2/build/src/spicy/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdo/Cti_Project/zeek-6.0.2/build/src/builtin-plugins/zeek-af_packet-plugin/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/zeek/share/zeek/builtin-plugins/__preload__.zeek")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/zeek/share/zeek/builtin-plugins" TYPE FILE FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/scripts/builtin-plugins/__preload__.zeek")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/zeek/share/zeek/builtin-plugins/__load__.zeek")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/zeek/share/zeek/builtin-plugins" TYPE FILE FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/scripts/builtin-plugins/__load__.zeek")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdo/Cti_Project/zeek-6.0.2/build/src/fuzzers/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/zeek/share/zeek/base/bif")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/zeek/share/zeek/base" TYPE DIRECTORY FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/scripts/base/bif")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/zeek/lib/zeek/plugins/")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/zeek/lib/zeek/plugins" TYPE DIRECTORY FILES "")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  
   file(REMOVE_RECURSE
       /usr/local/zeek/share/zeek/base/frameworks/logging/writers/dataseries.bro
       /usr/local/zeek/share/zeek/base/frameworks/logging/writers/elasticsearch.bro
       /usr/local/zeek/share/zeek/policy/tuning/logs-to-elasticsearch.bro
   )

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/zeek" TYPE DIRECTORY FILES "/home/abdo/Cti_Project/zeek-6.0.2/src/" FILES_MATCHING REGEX "/[^/]*\\.h$" REGEX "/[^/]*\\.pac$" REGEX "/3rdparty\\/[^/]*$" EXCLUDE REGEX "/home/abdo/Cti_Project/zeek-6\\.0\\.2/src/include/\\*$" EXCLUDE REGEX "/script\\_opt\\/CPP\\/maint$" EXCLUDE REGEX "/fuzzers\\/corpora$" EXCLUDE)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/zeek" TYPE DIRECTORY FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/src/" FILES_MATCHING REGEX "/[^/]*\\.bif\\.func\\_h$" REGEX "/[^/]*\\.bif\\.netvar\\_h$" REGEX "/[^/]*\\.bif\\.h$" REGEX "/CMakeFiles$" EXCLUDE REGEX "/home/abdo/Cti_Project/zeek-6\\.0\\.2/src/include/\\*$" EXCLUDE)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/zeek/3rdparty" TYPE FILE FILES
    "/home/abdo/Cti_Project/zeek-6.0.2/src/3rdparty/ConvertUTF.h"
    "/home/abdo/Cti_Project/zeek-6.0.2/src/3rdparty/bro_inet_ntop.h"
    "/home/abdo/Cti_Project/zeek-6.0.2/src/3rdparty/zeek_inet_ntop.h"
    "/home/abdo/Cti_Project/zeek-6.0.2/src/3rdparty/bsd-getopt-long.h"
    "/home/abdo/Cti_Project/zeek-6.0.2/src/3rdparty/modp_numtoa.h"
    "/home/abdo/Cti_Project/zeek-6.0.2/src/3rdparty/patricia.h"
    "/home/abdo/Cti_Project/zeek-6.0.2/src/3rdparty/setsignal.h"
    "/home/abdo/Cti_Project/zeek-6.0.2/src/3rdparty/sqlite3.h"
    "/home/abdo/Cti_Project/zeek-6.0.2/src/3rdparty/doctest.h"
    )
endif()

