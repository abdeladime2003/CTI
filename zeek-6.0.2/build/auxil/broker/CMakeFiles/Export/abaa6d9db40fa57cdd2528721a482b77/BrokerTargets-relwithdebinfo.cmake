#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "broker" for configuration "RelWithDebInfo"
set_property(TARGET broker APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(broker PROPERTIES
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libbroker.so.2.6"
  IMPORTED_SONAME_RELWITHDEBINFO "libbroker.so.4"
  )

list(APPEND _cmake_import_check_targets broker )
list(APPEND _cmake_import_check_files_for_broker "${_IMPORT_PREFIX}/lib/libbroker.so.2.6" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
