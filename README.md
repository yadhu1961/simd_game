# simd_game
Using vector instructions/bitwise operations for number crunching
Repository contains my experimentation with SIMD(vector) processing instructions for high performance implementation of math operations.
Additionally, bitwise operations to perform number crunching efficiently.

## Project Structure

- `fft/` - Fourier Transform implementations
            DFT implemented
            FFT ==> yet to be implmented
- `unit_tests/` - Unit tests and verification scripts
- `simd_matrix_ops/` - SIMD matrix operations
- `convolution/` - Convolution algorithms
- `checksum/` - Checksum calculations
- `crc_calc/` - CRC calculations
- `reverse_bits/` - Bit manipulation algorithms
- `bin/` - Compiled executables

## Building

```bash
mkdir -p build && cd build
cmake .. && make
```

## Testing

Run unit tests from the project root:
```bash
python3 unit_tests/verify_dtft.py
``` 
