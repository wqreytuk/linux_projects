cmake_minimum_required (VERSION 3.8)

project ("parent_child_process_fd_share")
add_subdirectory(lib)

list(APPEND EXTRA_LIBS lib)

add_executable(parent_child_process_fd_share "test.c")

target_link_libraries(parent_child_process_fd_share PUBLIC ${EXTRA_LIBS})
