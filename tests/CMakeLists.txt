# Motors tests target
add_executable(motors_test motors_test.c)
target_link_options(motors_test PRIVATE "-T${LINKER_SCRIPT}")
target_link_libraries(motors_test bsp)
target_include_directories(motors_test PRIVATE
  ../bsp/include/bsp
  ../bsp/include/CMSIS
  ../bsp/include/TM4C123  
  )

# Template test
# add_executable(example_test example_test.c)
# target_link_options(example_test PRIVATE "-T${LINKER_SCRIPT}")
# target_link_libraries(example_test bsp)
# target_include_directories(example_test PRIVATE
#   ../bsp/include/bsp
#   ../bsp/include/CMSIS
#   ../bsp/include/TM4C123  
#   )