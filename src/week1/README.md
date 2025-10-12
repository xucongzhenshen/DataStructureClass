# Boolean Combinations Printer

This small C++ program prints all possible combinations of n Boolean variables x1..xn and counts how many times each variable is true.

## Build (Windows)

Install a C++ compiler (e.g., MinGW-w64) and make sure `g++` is on your PATH.

Compile:

```powershell
g++ "d:\Program Files\Microsoft VS Code\DSClass\DS2025_32_2.cpp" -O2 -std=c++17 -o "d:\Program Files\Microsoft VS Code\DSClass\DS2025_32_2.exe"
```

Run:

```powershell
"d:\Program Files\Microsoft VS Code\DSClass\DS2025_32_2.exe"
```

Then input `n` when prompted (e.g., `3`).

## Example (n = 3)

Total combinations: 8

true, true, true
true, true, false
true, false, true
true, false, false
false, true, true
false, true, false
false, false, true
false, false, false

Frequency count (how many times each xi is true):

x1: 4 out of 8 (50%)
x2: 4 out of 8 (50%)
x3: 4 out of 8 (50%)

## Notes

- The program limits n to a practical value (default check up to 30) to avoid extremely large outputs.
- You can redirect output to a file if you want to inspect large numbers of combinations.
