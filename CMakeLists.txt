cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE cmake/toolchain-arm-none-eabi.cmake)

project(cster_robotic_arm)

add_library(bsp
    bsp/src/bsp_tm4c123.c
    bsp/src/bsp_tm4c123_led.c
    bsp/src/bsp_tm4c123_motor.c)

target_compile_definitions(bsp PUBLIC TM4C1233H6PM)
target_include_directories(bsp PRIVATE
    bsp/include/bsp
    bsp/include/CMSIS
    bsp/include/TM4C123)

add_executable(cster_robotic_arm main.c)
target_link_libraries(cster_robotic_arm bsp)
target_include_directories(cster_robotic_arm PRIVATE bsp/include/bsp)