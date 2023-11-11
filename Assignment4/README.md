# Matrix Multiplication Program

This program performs matrix multiplication in parallel using child processes. It incorporates robust error handling, efficient memory management with malloc, and utilizes the exec family of system calls for process execution. The program begins by reading matrices from files using the readMatrixFromFile function, implementing error handling to manage file opening failures. The core parallel computation is carried out in the executeMatrixMultParallel function, where a child process is forked to execute matrix multiplication. This involves redirecting standard output and error to separate files, handling potential errors in file opening, and employing the exec system call to replace the child process with the actual matrix multiplication executable (matrixmult_parallel). The main function orchestrates the entire process, validating command-line arguments, reading the initial matrix A, and employing dynamic memory allocation (malloc) to manage the matrix file names when matrices are provided interactively. The program ensures proper resource release using free after dynamically allocating memory. Overall, this code not only efficiently performs parallel matrix multiplication but also demonstrates good practices in error handling, process execution, and memory management.

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
## Runtime

This program has an average runtime of ~ 0.002 seconds