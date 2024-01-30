cmake_minimum_required(VERSION 3.18)

project(templelib)

cmake_policy(SET CMP0152 OLD)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/templelib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/templelib)

# Defines the stuff for the glyphsheet. To compile for platforms other than linux, you
# will have to change this stuff.
file(REAL_PATH ~/.templelib DATA_DIR)
set(GLYPHSHEET_FILE glyphsheet.png)
set(GLYPHSHEET_SOURCE data/glyphsheet.png)
file(REAL_PATH ${DATA_DIR}/${GLYPHSHEET_FILE} GLYPHSHEET_PATH)

add_definitions(-DGLYPH_SIZE=8)
add_definitions(-DGLYPHSHEET_PATH="${GLYPHSHEET_PATH}")

file(MAKE_DIRECTORY ${DATA_DIR})
if (NOT EXISTS ${GLYPHSHEET_PATH})
  file(COPY ${GLYPHSHEET_SOURCE}
    DESTINATION ${DATA_DIR}
  )
endif()

add_subdirectory(src)

add_subdirectory(demo)
