//
// Created by Sanjana Nagwekar on 11/13/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <time.h>
#include <limits.h>

#define MATRIX_SIZE 8
#define MAX_FILENAME_LENGTH 256 // Define the maximum length for filenames

// Function to read and pad a matrix to 8x8 from a file
void readMatrixFromFile(const char *filename, int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        char fullpath[PATH_MAX];
        if (realpath(filename, fullpath) != NULL) {
            fprintf(stderr, "Failed to open file: %s (full path: %s)\n", filename, fullpath);
        } else {
            fprintf(stderr, "Failed to open file: %s (path could not be resolved)\n", filename);
        }
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            if (fscanf(file, "%d", &matrix[i][j]) != 1) {
                // If we reach end-of-file or fail to read a number, pad the rest with zeros
                matrix[i][j] = 0;
            }
        }
    }
    fclose(file);
}

// Function to read and pad a matrix to 8x8 from stdin
void readMatrixFromStdin(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                // If we reach end-of-file or fail to read a number, pad the rest with zeros
                matrix[i][j] = 0;
            }
        }
    }
}

// Function to multiply two 8x8 matrices
void multiplyMatrices(int matA[MATRIX_SIZE][MATRIX_SIZE], int matB[MATRIX_SIZE][MATRIX_SIZE], int result[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                result[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <matrixW_filename>\n", argv[0]);
        return 1;
    }

    char aMatrixFilename[MAX_FILENAME_LENGTH];
    int matrixA[MATRIX_SIZE][MATRIX_SIZE];
    int matrixW[MATRIX_SIZE][MATRIX_SIZE];
    int resultMatrix[MATRIX_SIZE][MATRIX_SIZE];

    // Read matrix W from the file
    readMatrixFromFile(argv[1], matrixW);

    // Prepare the file to write output
    char outputFilename[20];
    sprintf(outputFilename, "%d.out", getpid());
    FILE *outputFile = fopen(outputFilename, "w");
    if (!outputFile) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    // Read matrix A filenames from stdin, then process each one
    while (fgets(aMatrixFilename, MAX_FILENAME_LENGTH, stdin) != NULL) {
        aMatrixFilename[strcspn(aMatrixFilename, "\n")] = 0; // Remove newline character
        printf("Received A matrix filename: %s\n", aMatrixFilename);  // Debugging statement

        readMatrixFromFile(aMatrixFilename, matrixA);
        multiplyMatrices(matrixA, matrixW, resultMatrix);

        // Write results to outputFile
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                fprintf(outputFile, "%d ", resultMatrix[i][j]);
            }
            fprintf(outputFile, "\n");
        }
    }

    // Clean up and close file
    fclose(outputFile);

    return 0;
}
