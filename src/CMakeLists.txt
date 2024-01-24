find_package(SDL2 REQUIRED SDL2)
find_package(SDL2_image REQUIRED)

file(GLOB templelib_sources *.c)
file(GLOB templelib_headers *.h)

add_library(templelib STATIC ${templelib_sources})

target_link_libraries(templelib PUBLIC SDL2::SDL2)
target_link_libraries(templelib PUBLIC SDL2_image)

file(COPY ${templelib_headers}
  DESTINATION "${CMAKE_SOURCE_DIR}/templelib/include"
)
