# Matrix Multiplication Using Threads (Assignment 6 - CS149)

## Project Overview
This project, matrixmult_threaded, is a multi-threaded program for performing matrix multiplication. It demonstrates the use of POSIX threads (pthread) and mutex locks to safely compute the product of two 8x8 matrices in a concurrent environment.

## Files Included

- matrixmult_threaded.c: The main C source file for the matrix multiplication program.
- A1.txt, W1.txt: Example input files representing matrices A and W, respectively.

## Compilation Instructions

To compile the program, use the following command in your terminal:

```bash
gcc -D_REENTRANT -pthread -o matrixmult_threaded matrixmult_threaded.c -Wall -Werror
```
This command will generate an executable named matrixmult_threaded.

## Running the Program
To run the program, use the following syntax:

```bash
./matrixmult_threaded path_to_matrix_A_file path_to_matrix_W_file
```
Replace path_to_matrix_A_file and path_to_matrix_W_file with the actual paths to your matrix files. For example:

```bash
./matrixmult_threaded A1.txt W1.txt
```
## Program Functionality
- The program reads two matrices from the provided files.
- It then multiplies these matrices using 64 threads, with each thread computing one cell of the result matrix.
- Mutex locks are used to ensure thread safety, particularly in scenarios where shared resources are accessed or modified.

## Input File Format
- Both input files should represent matrices.
- Each element in the matrix should be separated by a space.
- Each row of the matrix should be on a new line.

## Testing
To verify the program's basic functionality with standard input.

Input Files
- A1.txt: Contains a 1x3 matrix.
- W1.txt: Contains a 3x5 matrix.

How to Run:
```bash
./matrixmult_threaded A1.txt W1.txt
```
Expected Output:
The output will show the computed result matrix.

```bash
Matrix A:
 10  30  40  50  0  0  0  0 
 0  0  0  0  0  0  0  0 
 0  0  0  0  0  0  0  0 
 0  0  0  0  0  0  0  0 
 0  0  0  0  0  0  0  0 
 0  0  0  0  0  0  0  0 
 0  0  0  0  0  0  0  0 
 0  0  0  0  0  0  0  0 

Matrix W:
 1  3  4  5  1  0  0  0 
 2  4  5  0  0  0  0  0 
 1  1  5  0  0  0  0  0 
 0  0  0  0  0  0  0  0 
 0  0  0  0  0  0  0  0 
 0  0  0  0  0  0  0  0 
 0  0  0  0  0  0  0  0 
 0  0  0  0  0  0  0  0 

Result of A*W = [
110 190 390 50 10  0  0  0 
 0  0  0  0  0  0  0  0 
 0  0  0  0  0  0  0  0 
 0  0  0  0  0  0  0  0 
 0  0  0  0  0  0  0  0 
 0  0  0  0  0  0  0  0 
 0  0  0  0  0  0  0  0 
 0  0  0  0  0  0  0  0 
]
```
## Runtime Measurement
- Measure the runtime of the program using the time command.
- Example: time ./matrixmult_threaded A1.txt W1.txt
- Document the average runtime over multiple runs for accuracy.