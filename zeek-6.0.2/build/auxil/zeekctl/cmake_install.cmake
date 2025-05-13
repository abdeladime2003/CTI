# Install script for directory: /home/abdo/Cti_Project/zeek-6.0.2/auxil/zeekctl

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM RENAME "zeekctl" FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/bin/zeekctl.in.dehashbanged")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zeekctl/scripts" TYPE PROGRAM RENAME "archive-log" FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/bin/archive-log.dehashbanged")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zeekctl/scripts" TYPE PROGRAM RENAME "check-config" FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/bin/check-config.dehashbanged")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zeekctl/scripts" TYPE PROGRAM RENAME "crash-diag" FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/bin/crash-diag.dehashbanged")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zeekctl/scripts" TYPE PROGRAM RENAME "delete-log" FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/bin/delete-log.dehashbanged")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zeekctl/scripts" TYPE PROGRAM RENAME "expire-crash" FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/bin/expire-crash.dehashbanged")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zeekctl/scripts" TYPE PROGRAM RENAME "expire-logs" FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/bin/expire-logs.dehashbanged")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zeekctl/scripts" TYPE PROGRAM RENAME "make-archive-name" FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/bin/make-archive-name.dehashbanged")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zeekctl/scripts" TYPE PROGRAM RENAME "post-terminate" FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/bin/post-terminate.dehashbanged")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zeekctl/scripts" TYPE PROGRAM RENAME "run-zeek" FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/bin/run-zeek.dehashbanged")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zeekctl/scripts" TYPE PROGRAM RENAME "run-zeek-on-trace" FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/bin/run-zeek-on-trace.dehashbanged")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zeekctl/scripts" TYPE PROGRAM RENAME "send-mail" FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/bin/send-mail.dehashbanged")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zeekctl/scripts" TYPE PROGRAM RENAME "stats-to-csv" FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/bin/stats-to-csv.dehashbanged")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zeekctl/scripts/helpers" TYPE PROGRAM RENAME "check-pid" FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/bin/helpers/check-pid.dehashbanged")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zeekctl/scripts/helpers" TYPE PROGRAM RENAME "df" FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/bin/helpers/df.dehashbanged")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zeekctl/scripts/helpers" TYPE PROGRAM RENAME "first-line" FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/bin/helpers/first-line.dehashbanged")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zeekctl/scripts/helpers" TYPE PROGRAM RENAME "start" FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/bin/helpers/start.dehashbanged")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zeekctl/scripts/helpers" TYPE PROGRAM RENAME "stop" FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/bin/helpers/stop.dehashbanged")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zeekctl/scripts/helpers" TYPE PROGRAM RENAME "top" FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/bin/helpers/top.dehashbanged")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zeekctl/scripts/postprocessors" TYPE PROGRAM RENAME "summarize-connections" FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/bin/postprocessors/summarize-connections.dehashbanged")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/zeek/lib/zeek/python/zeekctl/ZeekControl")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/zeek/lib/zeek/python/zeekctl" TYPE DIRECTORY FILES "/home/abdo/Cti_Project/zeek-6.0.2/auxil/zeekctl/ZeekControl" REGEX "/options\\.py$" EXCLUDE REGEX "/ssh\\_runner\\.py$" EXCLUDE REGEX "/version\\.py$" EXCLUDE REGEX "/zeekctld\\.py$" EXCLUDE REGEX "/ser\\.py$" EXCLUDE REGEX "/test\\_cli\\.py$" EXCLUDE REGEX "/web\\.py$" EXCLUDE REGEX "/plugins[^/]*$" EXCLUDE)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/zeek/lib/zeek/python/zeekctl/ZeekControl/options.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/zeek/lib/zeek/python/zeekctl/ZeekControl" TYPE FILE FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/ZeekControl/options.py")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/zeek/lib/zeek/python/zeekctl/ZeekControl/ssh_runner.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/zeek/lib/zeek/python/zeekctl/ZeekControl" TYPE FILE FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/ZeekControl/ssh_runner.py")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/zeek/lib/zeek/python/zeekctl/ZeekControl/version.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/zeek/lib/zeek/python/zeekctl/ZeekControl" TYPE FILE FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/ZeekControl/version.py")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/zeek/lib/zeek/python/zeekctl/plugins")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/zeek/lib/zeek/python/zeekctl" TYPE DIRECTORY FILES "/home/abdo/Cti_Project/zeek-6.0.2/auxil/zeekctl/ZeekControl/plugins")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zeekctl/scripts/helpers" TYPE FILE FILES "/home/abdo/Cti_Project/zeek-6.0.2/auxil/zeekctl/bin/helpers/to-bytes.awk")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/zeekctl/scripts" TYPE FILE FILES "/home/abdo/Cti_Project/zeek-6.0.2/auxil/zeekctl/bin/set-zeek-path")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/zeek/share/man/man8/zeekctl.8")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/zeek/share/man/man8" TYPE FILE FILES "/home/abdo/Cti_Project/zeek-6.0.2/auxil/zeekctl/man/zeekctl.8")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/zeek/share/zeek/")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/zeek/share/zeek" TYPE DIRECTORY FILES "/home/abdo/Cti_Project/zeek-6.0.2/auxil/zeekctl/scripts/" FILES_MATCHING REGEX "/[^/]*\\.zeek$")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/zeek/spool/")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/zeek/spool" TYPE DIRECTORY FILES "")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/zeek/spool/tmp/")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/zeek/spool/tmp" TYPE DIRECTORY FILES "")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/zeek/spool/brokerstore/")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/zeek/spool/brokerstore" TYPE DIRECTORY FILES "")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/zeek/logs/")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/zeek/logs" TYPE DIRECTORY FILES "")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/zeek/spool/zeekctl-config.sh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/zeek/spool" TYPE FILE FILES "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/zeekctl-config.sh")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  
            if ("$ENV{DESTDIR}" STREQUAL "")
                execute_process(COMMAND "/usr/bin/cmake" -E create_symlink
                                /usr/local/zeek/spool/zeekctl-config.sh
                                /usr/local/zeek/share/zeekctl/scripts/zeekctl-config.sh)
            else ()
                execute_process(COMMAND "/usr/bin/cmake" -E create_symlink
                                /usr/local/zeek/spool/zeekctl-config.sh
                                $ENV{DESTDIR}//usr/local/zeek/share/zeekctl/scripts/zeekctl-config.sh)
            endif ()
        
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  
    if ( "$ENV{DESTDIR}" STREQUAL "" )
      if ( EXISTS "/usr/local/zeek/etc/broctl.cfg" AND NOT EXISTS "/usr/local/zeek/etc/zeekctl.cfg" )
        message(FATAL_ERROR "/usr/local/zeek/etc/broctl.cfg exists, but /usr/local/zeek/etc/zeekctl.cfg does not; rename it")
      endif ()
    endif ()
  
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  
        set(_destfile "/usr/local/zeek/etc/zeekctl.cfg")
        if (NOT "$ENV{DESTDIR}" STREQUAL "")
            # prepend install root prefix with install-time DESTDIR
            set(_destfile "$ENV{DESTDIR}//usr/local/zeek/etc/zeekctl.cfg")
        endif ()
        if (EXISTS ${_destfile})
            message(STATUS "Skipping: ${_destfile} (already exists)")
            execute_process(COMMAND "/usr/bin/cmake" -E compare_files
                /home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/etc/zeekctl.cfg ${_destfile} RESULT_VARIABLE _diff)
            if (NOT "${_diff}" STREQUAL "0")
                message(STATUS "Installing: ${_destfile}.example")
                configure_file(/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/etc/zeekctl.cfg ${_destfile}.example COPYONLY)
            endif ()
        else ()
            message(STATUS "Installing: ${_destfile}")
            # install() is not scriptable within install(), and
            # configure_file() is the next best thing
            configure_file(/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/etc/zeekctl.cfg ${_destfile} COPYONLY)
            # TODO: create additional install_manifest files?
        endif ()
    
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  
        set(_destfile "/usr/local/zeek/etc/networks.cfg")
        if (NOT "$ENV{DESTDIR}" STREQUAL "")
            # prepend install root prefix with install-time DESTDIR
            set(_destfile "$ENV{DESTDIR}//usr/local/zeek/etc/networks.cfg")
        endif ()
        if (EXISTS ${_destfile})
            message(STATUS "Skipping: ${_destfile} (already exists)")
            execute_process(COMMAND "/usr/bin/cmake" -E compare_files
                /home/abdo/Cti_Project/zeek-6.0.2/auxil/zeekctl/etc/networks.cfg ${_destfile} RESULT_VARIABLE _diff)
            if (NOT "${_diff}" STREQUAL "0")
                message(STATUS "Installing: ${_destfile}.example")
                configure_file(/home/abdo/Cti_Project/zeek-6.0.2/auxil/zeekctl/etc/networks.cfg ${_destfile}.example COPYONLY)
            endif ()
        else ()
            message(STATUS "Installing: ${_destfile}")
            # install() is not scriptable within install(), and
            # configure_file() is the next best thing
            configure_file(/home/abdo/Cti_Project/zeek-6.0.2/auxil/zeekctl/etc/networks.cfg ${_destfile} COPYONLY)
            # TODO: create additional install_manifest files?
        endif ()
    
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  
        set(_destfile "/usr/local/zeek/etc/node.cfg")
        if (NOT "$ENV{DESTDIR}" STREQUAL "")
            # prepend install root prefix with install-time DESTDIR
            set(_destfile "$ENV{DESTDIR}//usr/local/zeek/etc/node.cfg")
        endif ()
        if (EXISTS ${_destfile})
            message(STATUS "Skipping: ${_destfile} (already exists)")
            execute_process(COMMAND "/usr/bin/cmake" -E compare_files
                /home/abdo/Cti_Project/zeek-6.0.2/auxil/zeekctl/etc/node.cfg ${_destfile} RESULT_VARIABLE _diff)
            if (NOT "${_diff}" STREQUAL "0")
                message(STATUS "Installing: ${_destfile}.example")
                configure_file(/home/abdo/Cti_Project/zeek-6.0.2/auxil/zeekctl/etc/node.cfg ${_destfile}.example COPYONLY)
            endif ()
        else ()
            message(STATUS "Installing: ${_destfile}")
            # install() is not scriptable within install(), and
            # configure_file() is the next best thing
            configure_file(/home/abdo/Cti_Project/zeek-6.0.2/auxil/zeekctl/etc/node.cfg ${_destfile} COPYONLY)
            # TODO: create additional install_manifest files?
        endif ()
    
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  
    if ( "$ENV{DESTDIR}" STREQUAL "" )
      if ( EXISTS "/usr/local/zeek/lib/broctl" AND NOT IS_SYMLINK "/usr/local/zeek/lib/broctl" AND IS_DIRECTORY "/usr/local/zeek/lib/broctl" )
        message(STATUS "WARNING: removing old directory /usr/local/zeek/lib/broctl")
        execute_process(COMMAND "/usr/bin/cmake" -E rm -rf "/usr/local/zeek/lib/broctl")
      endif ()
    endif ()
  
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  
            if ("$ENV{DESTDIR}" STREQUAL "")
                execute_process(COMMAND "/usr/bin/cmake" -E create_symlink
                                /usr/local/zeek/lib/zeek/python/zeekctl
                                /usr/local/zeek/lib/broctl)
            else ()
                execute_process(COMMAND "/usr/bin/cmake" -E create_symlink
                                /usr/local/zeek/lib/zeek/python/zeekctl
                                $ENV{DESTDIR}//usr/local/zeek/lib/broctl)
            endif ()
        
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/zeek/lib/zeek/python/zeekctl/BroControl")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/zeek/lib/zeek/python/zeekctl" TYPE DIRECTORY FILES "/home/abdo/Cti_Project/zeek-6.0.2/auxil/zeekctl/BroControl")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/auxil/pysubnettree/cmake_install.cmake")
  include("/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/auxil/capstats/cmake_install.cmake")
  include("/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/zeekctl/auxil/trace-summary/cmake_install.cmake")

endif()

