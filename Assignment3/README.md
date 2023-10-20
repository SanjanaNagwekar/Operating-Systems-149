# Matrix Multiplication Parallelization

This repository contains a C program for parallel matrix multiplication. It allows you to execute multiple matrix multiplications in parallel by spawning child processes using the `fork` system call and then running matrix multiplication using the `exec` system call.

## Prerequisites

Before you can run this program, make sure you have the following installed on your system:

- C Compiler (e.g., GCC)
- Standard C Library
- Unix-like operating system (Linux, macOS, etc.)

## Compilation

To compile the program, use the following command:

```bash
gcc -o matrixmult_multiw matrixmult_multiw.c
```
This will generate an executable named matrixmult_multiw.

## Usage
You can use the program by providing a matrix A file and one or more matrix W files as command-line arguments. 
For example:
./matrixmult_multiw A1.txt W1.txt W2.txt W3.txt
A1.txt: The matrix A file.
W1.txt, W2.txt, W3.txt: Matrix W files to multiply with matrix A.

The program will spawn child processes for each matrix multiplication, execute the matrixmult_parallel program with the specified matrices, and create output and error files for each child process.

The program will create output files in the format PID.out and error files in the format PID.err where PID is the process ID of each child process. The output files contain information about the execution of each child process, such as the starting command, matrix contents, and results. The error files contain any error messages.

Here's an example of the output format for each child process:

```bash
$ cat 2353.out
Starting command 1: child 2353 pid of parent 2234
A1.txt=[...]
W1.txt=[...]
R=[
110 190 390  50 10 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
]
Finished child 2353 pid of parent 2234
Exited with exitcode = 0
```