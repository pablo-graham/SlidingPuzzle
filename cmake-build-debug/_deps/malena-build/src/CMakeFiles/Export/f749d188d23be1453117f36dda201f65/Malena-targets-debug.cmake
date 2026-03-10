#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Malena::Malena" for configuration "Debug"
set_property(TARGET Malena::Malena APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Malena::Malena PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libMalena.a"
  )

list(APPEND _cmake_import_check_targets Malena::Malena )
list(APPEND _cmake_import_check_files_for_Malena::Malena "${_IMPORT_PREFIX}/lib/libMalena.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
