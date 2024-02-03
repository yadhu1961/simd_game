cmake_minimum_required(VERSION 3.10)

project(SIMD_GAME
  VERSION
    1.0
  DESCRIPTION
    "SIMD Game"
  LANGUAGES
    C CXX
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(mat_mul mat_mul.c)

add_executable(simd_matrix_mul simd_matrix_mul.c)

add_executable(crc_cal crc_cal.c)

target_compile_options(crc_cal PRIVATE -std=c11 -Wall -Wextra -Wpedantic -g)

# add_custom_command(
#     TARGET stack_driver_test
#     POST_BUILD
#     COMMAND ${CMAKE_SOURCE_DIR}/bin/stack_driver_test
#     DEPENDS stack_driver_test
#     COMMENT "Running Stack example implementation test"
# )





