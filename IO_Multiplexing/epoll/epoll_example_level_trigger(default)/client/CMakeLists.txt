cmake_minimum_required (VERSION 3.8)

project ("client")
add_subdirectory(lib)

list(APPEND EXTRA_LIBS lib)

add_executable(client "main.cpp")

target_link_libraries(client PUBLIC pthread ${EXTRA_LIBS})
