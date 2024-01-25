find_package(SDL2 REQUIRED SDL2)
find_package(SDL2_image REQUIRED)

file(GLOB templelib_sources *.c)
file(GLOB templelib_headers *.h)

file(GLOB templelib_gr_sources Gr/*.c)
file(GLOB templelib_gr_headers Gr/*.h)

add_library(templelib STATIC ${templelib_sources} ${templelib_gr_sources})

target_link_libraries(templelib PUBLIC SDL2::SDL2)
target_link_libraries(templelib PUBLIC SDL2_image)

file(COPY ${templelib_headers} ${templelib_gr_headers}
  DESTINATION "${CMAKE_SOURCE_DIR}/templelib/include"
)

file(COPY ${templelib_gr_headers}
  DESTINATION "${CMAKE_SOURCE_DIR}/templelib/include/Gr"
)
