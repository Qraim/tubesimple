# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/tubesimple_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/tubesimple_autogen.dir/ParseCache.txt"
  "tubesimple_autogen"
  )
endif()
