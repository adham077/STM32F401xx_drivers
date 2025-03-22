# Install script for directory: /home/adhamwalaa/gitHub_Repos/ES45_ARM/COTS/MCAL

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/arm-none-eabi-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/adhamwalaa/gitHub_Repos/ES45_ARM/APPS/test/build/RCC/cmake_install.cmake")
  include("/home/adhamwalaa/gitHub_Repos/ES45_ARM/APPS/test/build/GPIO/cmake_install.cmake")
  include("/home/adhamwalaa/gitHub_Repos/ES45_ARM/APPS/test/build/NVIC/cmake_install.cmake")
  include("/home/adhamwalaa/gitHub_Repos/ES45_ARM/APPS/test/build/EXTI/cmake_install.cmake")
  include("/home/adhamwalaa/gitHub_Repos/ES45_ARM/APPS/test/build/SYSCFG/cmake_install.cmake")
  include("/home/adhamwalaa/gitHub_Repos/ES45_ARM/APPS/test/build/DMA/cmake_install.cmake")
  include("/home/adhamwalaa/gitHub_Repos/ES45_ARM/APPS/test/build/USART/cmake_install.cmake")
  include("/home/adhamwalaa/gitHub_Repos/ES45_ARM/APPS/test/build/SYSTICK/cmake_install.cmake")

endif()

