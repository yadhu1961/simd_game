#!/usr/bin/env python3
import numpy as np
import cmath

def dtft_python(signal, N):
    """Compute DTFT using NumPy's FFT as reference implementation"""
    return np.fft.fft(signal)

def main():
    # Same input signal as in the C code
    signal = [-1, 1, 2, 1, 4, -2, 6, -8]
    N = 8
    
    # Compute DTFT using Python
    result = dtft_python(signal, N)
    
    # Expected output from C code (rounded to 1 decimal place)
    expected = [
        complex(3.0, 0.0),
        complex(-9.2, -4.5),
        complex(-5.0, -6.0),
        complex(-0.8, -12.5),
        complex(19.0, 0.0),
        complex(-0.8, 12.5),
        complex(-5.0, 6.0),
        complex(-9.2, 4.5)
    ]
    
    print("Input signal:", signal)
    print("\nPython DTFT result:")
    for i, val in enumerate(result):
        print(f"X[{i}] = ({val.real:.1f}, {val.imag:.1f}i)")
    
    print("\nC code result:")
    for i, val in enumerate(expected):
        print(f"X[{i}] = ({val.real:.1f}, {val.imag:.1f}i)")
    
    print("\nVerification:")
    all_correct = True
    for i, (py_val, c_val) in enumerate(zip(result, expected)):
        # Check if values are close (within 0.1 tolerance)
        if abs(py_val.real - c_val.real) > 0.1 or abs(py_val.imag - c_val.imag) > 0.1:
            print(f"❌ X[{i}]: Python=({py_val.real:.1f}, {py_val.imag:.1f}i), C=({c_val.real:.1f}, {c_val.imag:.1f}i)")
            all_correct = False
        else:
            print(f"✅ X[{i}]: ({py_val.real:.1f}, {py_val.imag:.1f}i)")
    
    if all_correct:
        print("\n🎉 All results match! The C implementation is correct.")
    else:
        print("\n❌ Some results don't match. There may be an issue with the C implementation.")

if __name__ == "__main__":
    main() 