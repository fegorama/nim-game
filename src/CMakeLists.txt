# Author: Fernando González Ruano (fegorsoft.com)
# SPDX-License-Identifier: mit

cmake_minimum_required(VERSION 3.25)

project(nim-game VERSION 1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set_source_files_properties(PROPERTIES LANGUAGE C_STANDARD)

set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")

add_compile_options(
  "-Wall" "-Wpedantic" "-Wextra" "-fexceptions"
  "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
)

add_custom_target(documentation SOURCES ../README.md)

add_executable(
  ${PROJECT_NAME} 
  main.c
  )

target_include_directories(${PROJECT_NAME} PRIVATE ../include)

target_compile_features(${PROJECT_NAME} PRIVATE c_std_11)

include(GNUInstallDirs)
 
install(TARGETS ${PROJECT_NAME}
    DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
