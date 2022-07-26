cmake_minimum_required (VERSION 3.8)

project ("server")
add_subdirectory(lib)

list(APPEND EXTRA_LIBS lib)

add_executable(server "main.cpp")

target_link_libraries(server PUBLIC pthread ${EXTRA_LIBS})
