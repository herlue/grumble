cmake_minimum_required(VERSION 3.16)
project(grumble VERSION 1.0.0 LANGUAGES C)

add_library(grumble STATIC src/grumble.c)

target_include_directories(grumble PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(grumble::grumble ALIAS grumble)
