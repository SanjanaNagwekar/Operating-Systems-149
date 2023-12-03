# Matrix Multiplication Project (Assignment 5 - CS149)

## Overview

This project is part of the CS149 course, focusing on advanced C programming, memory management, inter-process communication, and dynamic memory allocation. The main objective is to create a program (matrixmult_multiwa.c) that continuously accepts 8x8 matrices (A matrices) from standard input and performs matrix multiplication with predefined W matrices in parallel child processes. The child processes use a modified version of the matrixmult_parallel.c program from Assignment 2.


## Files
- matrixmult_multiwa.c: Main program that forks child processes and sends A matrix data to them.
- matrixmult_parallel.c: Modified version from Assignment 2, which performs matrix multiplication in child processes.
- README.md: This file, containing instructions and information about the project.

## Compilation

To compile the programs, use the following GCC commands:

```bash
gcc -o matrixmult_multiwa matrixmult_multiwa.c -Wall -Werror
gcc -o matrixmult_parallel matrixmult_parallel.c -Wall -Werror
```
This will create two executable files: matrixmult_multiwa and matrixmult_parallel.

## Running the Program
Run the matrixmult_multiwa program with the following command:

```bash
./matrixmult_multiwa A1.txt W1.txt W2.txt W3.txt
```
After starting the program, input additional A matrix filenames (e.g., A2.txt, A3.txt) one per line. To end the input stream and trigger the child processes to finalize their computations and exit, use Ctrl-D (EOF) in the terminal.

You can also run the program with input redirection or a pipe:

```bash
./matrixmult_multiwa A1.txt W1.txt W2.txt W3.txt < cmds.txt
cat cmds.txt | ./matrixmult_multiwa A1.txt W1.txt W2.txt W3.txt
```

## Output
Each child process writes its results to a file named PID.out, where PID is the process ID. The output file includes the filenames of all A and W matrices and the resulting R matrix after all computations.

## Testing
Test the program with various A matrix inputs to ensure it functions correctly. Example test files (e.g., A1.txt, A2.txt, A3.txt) should be provided in the test directory.

## Memory Management
The program uses dynamic memory allocation to handle the varying number of A matrices. Ensure no memory leaks are present by using tools like valgrind.

## Additional Notes
Ensure that the matrixmult_parallel executable is in the same directory as matrixmult_multiwa or adjust the exec call accordingly.
The project is designed for Linux/Unix environments and may require modifications for other operating systems.
For detailed information about the project structure and specific functionalities, refer to the inline comments in the source code.