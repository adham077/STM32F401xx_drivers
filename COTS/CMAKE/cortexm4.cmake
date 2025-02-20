set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(C_PATH "/usr/bin")

set(CMAKE_C_COMPILER ${C_PATH}/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER ${C_PATH}/arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER ${C_PATH}/arm-none-eabi-gcc)

set(CMAKE_SIZE ${C_PATH}/arm-none-eabi-size)
set(CMAKE_OBJCOPY ${C_PATH}/arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP ${C_PATH}/arm-none-eabi-objdump)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)