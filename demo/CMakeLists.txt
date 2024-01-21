add_executable(demo main.c)

include(CMakePrintHelpers)

target_link_libraries(demo PRIVATE templelib)
target_include_directories(demo PRIVATE "${CMAKE_SOURCE_DIR}/templelib/include")
