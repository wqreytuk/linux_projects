cmake_minimum_required (VERSION 3.8)

project ("client")
add_subdirectory(lib)

list(APPEND EXTRA_LIBS lib)

add_executable(client "tcpclient01.c")

target_link_libraries(client PUBLIC ${EXTRA_LIBS})
