﻿file(GLOB SOURCES "*.cpp")
add_library(lib ${SOURCES})

target_include_directories(lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})