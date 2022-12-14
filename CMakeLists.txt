cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE cmake/toolchain-arm-none-eabi.cmake)

project(cster_robotic_arm)

option(BUILD_TESTS "Build tests programs" OFF)

add_library(bsp
    bsp/src/bsp_tm4c123.c
    bsp/src/bsp_tm4c123_led.c
    bsp/src/bsp_tm4c123_motor.c
    bsp/src/bsp_tm4c123_uart.c
    bsp/src/bsp_tm4c123_udma.c
    bsp/src/bsp_tm4c123_ringbuffer.c
    bsp/startup/startup_tm4c1233h6pm.c
    )

add_library(freertos
    third_party/FreeRTOS-Kernel/croutine.c
    third_party/FreeRTOS-Kernel/event_groups.c
    third_party/FreeRTOS-Kernel/list.c
    third_party/FreeRTOS-Kernel/queue.c
    third_party/FreeRTOS-Kernel/stream_buffer.c
    third_party/FreeRTOS-Kernel/tasks.c
    third_party/FreeRTOS-Kernel/timers.c
    third_party/FreeRTOS-Kernel/portable/GCC/ARM_CM4F/port.c
    third_party/FreeRTOS-Kernel/portable/MemMang/heap_1.c
    )

add_library(control
  control/src/pid.c
  )

target_compile_definitions(bsp PUBLIC TM4C1233H6PM)
target_include_directories(bsp PRIVATE
    bsp/include/bsp
    bsp/include/CMSIS
    bsp/include/TM4C123
    )

target_include_directories(freertos PRIVATE
    third_party/FreeRTOS-Kernel/include
    third_party/FreeRTOS-Kernel/portable/GCC/ARM_CM4F
    .
    )

target_include_directories(control PRIVATE
  control/include
  )

set(LINKER_SCRIPT "${CMAKE_CURRENT_LIST_DIR}/bsp/linker_scripts/tm4c1233h6pm_minimal.ld")
add_executable(cster_robotic_arm main.c)
target_link_options(cster_robotic_arm PRIVATE "-T${LINKER_SCRIPT}")
target_link_libraries(cster_robotic_arm bsp freertos control)
target_include_directories(cster_robotic_arm PRIVATE 
    bsp/include/bsp
    control/include
    third_party/FreeRTOS-Kernel/include
    third_party/FreeRTOS-Kernel/portable/GCC/ARM_CM4F
    .
    )

# Custom targets to flash and debug the board
set(OPENOCD_SCRIPT_PATH "")
if(CMAKE_HOST_SYSTEM MATCHES Windows)
  set(OPENOCD_SCRIPT_PATH "C:/openocd/share/openocd/scripts/board/ti_ek-tm4c123gxl.cfg")
elseif(CMAKE_HOST_SYSTEM MATCHES Linux)
  set(OPENOCD_SCRIPT_PATH "/usr/local/share/openocd/scripts/board/ti_ek-tm4c123gxl.cfg")
endif()

add_custom_target(flash
    COMMAND openocd -f "${OPENOCD_SCRIPT_PATH}"
    -c "program ${CMAKE_BINARY_DIR}/cster_robotic_arm reset exit"
    DEPENDS cster_robotic_arm)

add_custom_target(debug
    COMMAND openocd -f /"${OPENOCD_SCRIPT_PATH}" &
    arm-none-eabi-gdb ${CMAKE_BINARY_DIR}/cster_robotic_arm 
    -ex "target extended-remote localhost:3333" -ex "load" -ex "break main"
    DEPENDS cster_robotic_arm)

#Compile tests
if(BUILD_TESTS)
  add_subdirectory(tests)
endif()