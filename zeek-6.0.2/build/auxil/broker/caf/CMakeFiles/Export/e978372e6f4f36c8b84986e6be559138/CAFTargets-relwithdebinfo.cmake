#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "CAF::core" for configuration "RelWithDebInfo"
set_property(TARGET CAF::core APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(CAF::core PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libcaf_core.a"
  )

list(APPEND _cmake_import_check_targets CAF::core )
list(APPEND _cmake_import_check_files_for_CAF::core "${_IMPORT_PREFIX}/lib/libcaf_core.a" )

# Import target "CAF::io" for configuration "RelWithDebInfo"
set_property(TARGET CAF::io APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(CAF::io PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libcaf_io.a"
  )

list(APPEND _cmake_import_check_targets CAF::io )
list(APPEND _cmake_import_check_files_for_CAF::io "${_IMPORT_PREFIX}/lib/libcaf_io.a" )

# Import target "CAF::net" for configuration "RelWithDebInfo"
set_property(TARGET CAF::net APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(CAF::net PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libcaf_net.a"
  )

list(APPEND _cmake_import_check_targets CAF::net )
list(APPEND _cmake_import_check_files_for_CAF::net "${_IMPORT_PREFIX}/lib/libcaf_net.a" )

# Import target "CAF::openssl" for configuration "RelWithDebInfo"
set_property(TARGET CAF::openssl APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(CAF::openssl PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libcaf_openssl.a"
  )

list(APPEND _cmake_import_check_targets CAF::openssl )
list(APPEND _cmake_import_check_files_for_CAF::openssl "${_IMPORT_PREFIX}/lib/libcaf_openssl.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
