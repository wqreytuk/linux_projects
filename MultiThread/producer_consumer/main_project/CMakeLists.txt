cmake_minimum_required (VERSION 3.8)

project ("mpc")
add_subdirectory(lib)

list(APPEND EXTRA_LIBS lib)

add_executable(mpc "main.c")

target_link_libraries(mpc PUBLIC pthread ${EXTRA_LIBS})
