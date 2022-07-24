cmake_minimum_required (VERSION 3.8)

project ("test")
add_subdirectory(lib)

list(APPEND EXTRA_LIBS lib)

add_executable(test "main.cpp")

target_link_libraries(test PUBLIC pthread ${EXTRA_LIBS})
