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

add_executable(mat_mul ${CMAKE_SOURCE_DIR}/simd_matrix_ops/mat_mul.c)

if(NOT APPLE OR NOT CMAKE_SYSTEM_PROCESSOR MATCHES "arm64") # since simd_matrix uses AVX2, it is not supported on arm64
    add_executable(simd_matrix_mul ${CMAKE_SOURCE_DIR}/simd_matrix_ops/simd_matrix_mul.c)
endif()

add_executable(crc_cal ${CMAKE_SOURCE_DIR}/crc_calc/crc_cal.c)

add_executable(convolution ${CMAKE_SOURCE_DIR}/convolution/convolution.c)

add_executable(reverse_bits ${CMAKE_SOURCE_DIR}/reverse_bits/reverse_bits.c)

add_executable(checksum ${CMAKE_SOURCE_DIR}/checksum/checksum.c)

add_executable(dtft ${CMAKE_SOURCE_DIR}/fft/dtft.c)

target_compile_options(mat_mul PRIVATE -std=c11 -Wall -Wextra -Wpedantic -g)

if(NOT APPLE OR NOT CMAKE_SYSTEM_PROCESSOR MATCHES "arm64")
    target_compile_options(simd_matrix_mul PRIVATE -std=c11 -Wall -Wextra -Wpedantic -g -march=native -mavx2)
endif()

target_compile_options(crc_cal PRIVATE -std=c11 -Wall -Wextra -Wpedantic -g)
target_compile_options(convolution PRIVATE -std=c11 -Wall -Wextra -Wpedantic -g)
target_compile_options(reverse_bits PRIVATE -std=c11 -Wall -Wextra -Wpedantic -g)
target_compile_options(checksum PRIVATE -std=c11 -Wall -Wextra -Wpedantic -g)
target_compile_options(dtft PRIVATE -std=c11 -Wall -Wextra -Wpedantic -g)





