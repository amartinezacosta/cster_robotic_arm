# Motors tests target
add_executable(motors_test motors_test.c)
target_link_options(motors_test PRIVATE "-T${LINKER_SCRIPT}")
target_link_libraries(motors_test bsp)
target_include_directories(motors_test PRIVATE
  ../bsp/include/bsp
  ../bsp/include/CMSIS
  ../bsp/include/TM4C123  
  )


add_executable(uart_test uart_test.c)
target_link_options(uart_test PRIVATE "-T${LINKER_SCRIPT}")
target_link_libraries(uart_test bsp)
target_include_directories(uart_test PRIVATE
  ../bsp/include/bsp
  ../bsp/include/CMSIS
  ../bsp/include/TM4C123  
  )

add_custom_target(flash_uart_test
    COMMAND openocd -f "${OPENOCD_SCRIPT_PATH}"
    -c "program ${CMAKE_BINARY_DIR}/tests/uart_test reset exit"
    DEPENDS uart_test)

add_custom_target(debug_uart_test
    COMMAND openocd -f /"${OPENOCD_SCRIPT_PATH}" &
    arm-none-eabi-gdb ${CMAKE_BINARY_DIR}/tests/uart_test 
    -ex "target extended-remote localhost:3333" -ex "load" -ex "break main"
    DEPENDS uart_test)

# Template test
# add_executable(example_test example_test.c)
# target_link_options(example_test PRIVATE "-T${LINKER_SCRIPT}")
# target_link_libraries(example_test bsp)
# target_include_directories(example_test PRIVATE
#   ../bsp/include/bsp
#   ../bsp/include/CMSIS
#   ../bsp/include/TM4C123  
#   )