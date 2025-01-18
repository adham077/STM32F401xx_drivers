cmake_minimum_required(VERSION 3.11)
project(test C ASM)

set(CMAKE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../COTS/CMAKE")
set(BUILD_TOOLS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../COTS/COMMON")
set(APP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c")
set(MCAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../COTS/MCAL)

include("${CMAKE_DIR}/cortexm4.cmake")

set(MCU cortex-m4)
set(F_CPU 84000000) 

set(STARTUP_FILE "${BUILD_TOOLS_DIR}/startup.c")
set(LINKER_SCRIPT "${BUILD_TOOLS_DIR}/stm32f401cc.ld")

add_executable(${PROJECT_NAME} ${APP_DIR})

add_subdirectory("${MCAL_DIR}/RCC" "${CMAKE_BINARY_DIR}/RCC")

target_link_libraries(${PROJECT_NAME} PUBLIC RCC)

target_compile_options(${PROJECT_NAME} PRIVATE
    -mcpu=${MCU}
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
    -Wall
    -Wextra
    ${DEBUG_FLAGS}
    -ffunction-sections
    -fdata-sections
)

target_link_options(${PROJECT_NAME} PRIVATE
    -T${LINKER_SCRIPT}
    -mcpu=${MCU}
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
    -specs=nano.specs
    -specs=nosys.specs
    -Wl,--gc-sections
    -Wl,-Map=${PROJECT_NAME}.map
    ${DEBUG_FLAGS}
)

add_executable(${PROJECT_NAME} ${APP_DIR})

add_subdirectory("${MCAL_DIR}/RCC" "${CMAKE_BINARY_DIR}/RCC")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND arm-none-eabi-objcopy -O binary ${PROJECT_NAME} ${PROJECT_NAME}.bin
    COMMAND arm-none-eabi-objcopy -O ihex ${PROJECT_NAME} ${PROJECT_NAME}.hex
    COMMENT "Generating binary and hex files"
)

# Optional: Add size information
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND arm-none-eabi-size ${PROJECT_NAME}
    COMMENT "Displaying size information"
)