# Matrix Multiplication Program

This program performs matrix multiplication in parallel using child processes. It reads a matrix from a file and multiplies it with multiple matrices in parallel.

## Compilation

To compile the program, use the following commands:

```bash
cc matrixmult_parallel.c -o matrixmult_parallel
cc matrixmult_multiw_deep.c -o matrixmult_multiw_deep
```
## Usage
matrixmult_parallel

The matrixmult_parallel program takes two file arguments representing matrices and performs matrix multiplication in parallel. For example:
```bash
cc ./matrixmult_parallel matrix_A.txt matrix_W.txt
```
matrixmult_multiw_deep

The matrixmult_multiw_deep program reads a base matrix (matrix A) and multiplies it with multiple matrices (matrix W) in parallel. It supports reading additional matrices from the command line and stdin. For example:
```bash
cc ./matrixmult_multiw_deep matrix_A.txt matrix_W1.txt matrix_W2.txt ... matrix_W8.txt
```
## Output

The result of matrix multiplication is printed to stdout in the format:
```bash
Rsum = [ ... ]  # Resultant matrix
Process finished with exit code 0
```
