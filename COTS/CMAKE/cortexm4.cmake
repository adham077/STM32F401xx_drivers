set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Path to ARM GCC toolchain
set(TOOLCHAIN_PATH "/usr/bin")

set(CMAKE_C_COMPILER ${TOOLCHAIN_PATH}/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PATH}/arm-none-eabi-gcc)

set(CMAKE_SIZE ${TOOLCHAIN_PATH}/arm-none-eabi-size)
set(CMAKE_OBJCOPY ${TOOLCHAIN_PATH}/arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP ${TOOLCHAIN_PATH}/arm-none-eabi-objdump)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Compiler and linker flags
set(CPU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CPU_FLAGS} -Wall -Wextra -ffunction-sections -fdata-sections -O0 -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CPU_FLAGS} -Wall -Wextra -ffunction-sections -fdata-sections -O0 -g")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${CPU_FLAGS} -O0 -g")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections -T${CMAKE_CURRENT_SOURCE_DIR}/../../COTS/COMMON/linkerscript.ld -Wl,-Map=${CMAKE_BINARY_DIR}/info.map")
