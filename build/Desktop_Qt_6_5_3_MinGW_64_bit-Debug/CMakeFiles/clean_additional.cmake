# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Book_autogen"
  "CMakeFiles\\Book_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Book_autogen.dir\\ParseCache.txt"
  )
endif()
