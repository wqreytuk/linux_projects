cmake_minimum_required (VERSION 3.8)

project ("server")
add_subdirectory(lib)

list(APPEND EXTRA_LIBS lib)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/lib")

add_executable(server "tcpserver01.c")

target_link_libraries(server PUBLIC ${EXTRA_LIBS})

target_include_directories(server PUBLIC ${EXTRA_INCLUDES})
