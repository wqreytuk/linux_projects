cmake_minimum_required (VERSION 3.8)

project ("webserver")
add_subdirectory(lib)

list(APPEND EXTRA_LIBS lib)

add_executable(webserver "main.cpp")

target_link_libraries(webserver PUBLIC pthread ${EXTRA_LIBS})
