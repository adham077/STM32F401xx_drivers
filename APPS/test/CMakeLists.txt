cmake_minimum_required(VERSION 3.11)
set(CMAKE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../COTS/CMAKE")

include("${CMAKE_DIR}/cortexm4.cmake")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfpu=vfpv3 -mfloat-abi=hard")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfpu=vfpv3 -mfloat-abi=hard")


project(test C ASM)

set(BUILD_TOOLS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../COTS/COMMON")
set(APP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c")
set(MCAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../COTS/MCAL)
set(HAL_LIBS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../COTS/HAL")
set(MCU cortex-m4)
set(F_CPU 84000000) 

set(STARTUP_FILE "${BUILD_TOOLS_DIR}/startup.c")
set(LINKER_SCRIPT "${BUILD_TOOLS_DIR}/stm32f401cc.ld")

add_executable(${PROJECT_NAME} ${APP_DIR})

set(CMAKE_EXECUTABLE_SUFFIX ".elf")


target_compile_options(${PROJECT_NAME} PRIVATE
    -mcpu=${MCU}
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
    -Wall
    -Wextra
    -O0
    -g
    ${DEBUG_FLAGS}
    -ffunction-sections
    -fdata-sections
)

target_link_options(${PROJECT_NAME} PRIVATE
    -T${LINKER_SCRIPT}
    -mcpu=${MCU}
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
    -specs=nano.specs
    -specs=nosys.specs
    -Wl,--gc-sections
    -O0
    -g
    -Wl,-Map=${PROJECT_NAME}.map
    ${DEBUG_FLAGS}
)

add_library(STARTUP STATIC
    ${STARTUP_FILE}
 )
add_subdirectory(${HAL_LIBS_PATH}  "${CMAKE_BINARY_DIR}/HAL_LIBS")

target_link_libraries(${PROJECT_NAME} PUBLIC STARTUP)

target_link_libraries(${PROJECT_NAME} PUBLIC HAL_lib)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND arm-none-eabi-objcopy -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
    COMMAND arm-none-eabi-objcopy -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    COMMENT "Generating binary and hex files"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND arm-none-eabi-size ${PROJECT_NAME}.elf
    COMMENT "Displaying size information"
)