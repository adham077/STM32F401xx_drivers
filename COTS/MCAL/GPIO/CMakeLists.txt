cmake_minimum_required(VERSION 3.11)
project(GPIO C)

add_library(GPIO STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GPIO.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GPIO_CFG.c
)

target_include_directories(GPIO PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../STD_LIB/
)