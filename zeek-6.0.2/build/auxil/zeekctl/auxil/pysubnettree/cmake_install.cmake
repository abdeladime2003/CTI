# Install script for directory: /home/abdo/Cti_Project/zeek-6.0.2/auxil/zeekctl/auxil/pysubnettree

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

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/zeek/lib/zeek/python/SubnetTree.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/zeek/lib/zeek/python" TYPE FILE FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/auxil/pysubnettree/SubnetTree.py")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/zeek/lib/zeek/python/_SubnetTree.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/zeek/lib/zeek/python/_SubnetTree.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/zeek/lib/zeek/python/_SubnetTree.so"
         RPATH "/usr/local/zeek/lib")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/zeek/lib/zeek/python/_SubnetTree.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/zeek/lib/zeek/python" TYPE MODULE FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/auxil/pysubnettree/_SubnetTree.so")
  if(EXISTS "$ENV{DESTDIR}/usr/local/zeek/lib/zeek/python/_SubnetTree.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/zeek/lib/zeek/python/_SubnetTree.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/usr/local/zeek/lib/zeek/python/_SubnetTree.so"
         OLD_RPATH ":::::::::::::::::::"
         NEW_RPATH "/usr/local/zeek/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/zeek/lib/zeek/python/_SubnetTree.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/auxil/pysubnettree/CMakeFiles/SubnetTree.dir/install-cxx-module-bmi-RelWithDebInfo.cmake" OPTIONAL)
endif()

