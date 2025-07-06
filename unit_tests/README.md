# Unit Tests

This directory contains unit tests and verification scripts for the SIMD Game project.

## Contents

- `verify_dtft.py` - Verification script for the Discrete Time Fourier Transform (DTFT) implementation
  - Compares C implementation results with Python reference implementation
  - Validates mathematical correctness of the DTFT algorithm
  - Tests the input signal: `[-1, 1, 2, 1, 4, -2, 6, -8]`

## Running Tests

```bash
# Run DTFT verification
python3 verify_dtft.py
```

## Adding New Tests

When adding new unit tests:
1. Use descriptive filenames (e.g., `test_<function_name>.py`)
2. Include clear documentation of what the test validates
3. Update this README with new test descriptions
4. Ensure tests can be run independently 