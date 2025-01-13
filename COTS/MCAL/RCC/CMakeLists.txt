cmake_minimum_required(VERSION 3.17.0)
project(RCC C)

set(RCC_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(RCC_INC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/inc")
set(STD_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../STD_LIB")
add_library(RCC STATIC
    ${RCC_LIB_PATH}/rcc.c
)

target_include_directories(RCC PRIVATE
    "${RCC_LIB_PATH}"
)

target_include_directories(RCC PUBLIC
    "${RCC_INC_PATH}"
    "${STD_LIB_PATH}"
)