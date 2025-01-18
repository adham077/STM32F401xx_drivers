cmake_minimum_required(VERSION 3.11)
project(RCC C)

add_library(RCC STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rcc.c
)

target_include_directories(RCC PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../STD_LIB/
)

target_include_directories(RCC PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)