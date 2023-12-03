# Matrix Multiplication and Cosine Distance Calculation Program

## Overview
This program (extension of Assignment 1) performs matrix multiplication and addition, then computes the cosine distance between the resulting vector and a provided "correct" vector. It's designed to handle matrices of fixed sizes as defined in the program.

## How to Compile and Run
To compile the program, use the following command (assuming you are using gcc):
```bash
gcc -o matrixmult matrixmult.c -lm
```
To run the program, use the following syntax:
```bash
./matrixmult <matrix_A_file> <matrix_W_file> <matrix_B_file> <correct_vector_file>
```
Replace <matrix_A_file>, <matrix_W_file>, <matrix_B_file>, and <correct_vector_file> with the paths to your input files.

## Test Cases

### Test Case 1
To verify the program's basic functionality with standard input.

Input Files
- A1.txt: Contains a 1x3 matrix.
- W1.txt: Contains a 3x5 matrix.
- B1.txt: Contains a 1x5 matrix.
- C1.txt: Contains a 1x5 vector.

How to Run:
```bash
./matrixmult A1.txt W1.txt B1.txt C1.txt
```
Expected Output:
The output will show the computed result matrix and a corresponding cosine distance. This verifies the correct execution of matrix operations and cosine similarity computation.

```bash
Closest matrix index: 0
Filename of weight matrix: W1.txt
Result vector: [ 271  151  191  81  41 ]
Cosine: 0.982246
```

### Test Case 2
To test how the program handles matrices and vectors filled with zeros.

Input Files

- A2.txt: A 1x3 matrix with all zeros. 
- W2.txt: A 3x5 matrix with all zeros.
- B2.txt: A 1x5 matrix with all zeros. 
- C2.txt: A 1x5 vector with all zeros.

How to Run:
```bash
./matrixmult A2.txt W2.txt B2.txt C2.txt
```
Expected Output:
The result should be a zero vector. The cosine distance should be handled to avoid undefined behavior (cosine similarity is undefined for zero vectors).

```bash
No closest matrix found.
Process finished with exit code 0
```

### Test Case 3
To verify how the program handles files with extra/missing data.

Input Files:
- A3.txt: A 1x3 matrix with extra values.
- W3.txt: A 3x5 matrix with some values missing.
- B3.txt: A 1x5 matrix with some values missing.
- C3.txt: A 1x5 vector with some values missing.

How to Run:
```bash
./matrixmult A3.txt W3.txt B3.txt C3.txt
```
Expected Output:
The program should fill missing values with zeros, compute the result, and calculate the cosine distance correctly.

```bash
Closest matrix index: 0
Filename of weight matrix: W3.txt
Result vector: [ 52  64  11  8  16 ]
Cosine: 0.593934
Process finished with exit code 0
```