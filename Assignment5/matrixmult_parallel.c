// matrixmult_parallel.c
// Created by Sanjana Nagwekar on 11/13/23.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

#define MATRIX_SIZE 8
#define MAX_FILENAME_LENGTH 256
#define TERMINATION_SIGNAL "END_OF_INPUT"

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

    // Read matrix W from the file
    fprintf(stdout, "Reading W matrix from file: %s\n", argv[1]); // Debugging statement
    readMatrixFromFile(argv[1], matrixW);

    // Prepare the file to write output
    char outputFilename[20];
    sprintf(outputFilename, "%d.out", getpid());
    FILE *outputFile = fopen(outputFilename, "w");
    if (!outputFile) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    // Dynamically allocate memory for result matrix R
    int numberOfMatrices = 0;
    int (*R)[MATRIX_SIZE] = NULL;

    // Read matrix A filenames from stdin, then process each one
    while (fgets(aMatrixFilename, MAX_FILENAME_LENGTH, stdin) != NULL) {
        aMatrixFilename[strcspn(aMatrixFilename, "\n")] = 0; // Remove newline character
        if (strcmp(aMatrixFilename, TERMINATION_SIGNAL) == 0) {
            break; // Exit loop on receiving termination signal
        }
        if (strlen(aMatrixFilename) == 0) {
            continue; // Skip empty lines
        }

        fprintf(stdout, "Received A matrix filename: %s\n", aMatrixFilename); // Debugging statement


        readMatrixFromFile(aMatrixFilename, matrixA);

        // Reallocate R to accommodate the new result
        numberOfMatrices++;
        R = realloc(R, numberOfMatrices * MATRIX_SIZE * MATRIX_SIZE * sizeof(int));
        if (R == NULL) {
            perror("realloc");
            fclose(outputFile);
            exit(EXIT_FAILURE);
        }

        int resultMatrix[MATRIX_SIZE][MATRIX_SIZE];
        multiplyMatrices(matrixA, matrixW, resultMatrix);

        // Copy the result to the correct position in R
        for (int i = 0; i < MATRIX_SIZE; i++) {
            memcpy(R[(numberOfMatrices - 1) * MATRIX_SIZE + i], resultMatrix[i], MATRIX_SIZE * sizeof(int));
        }
    }

    // Write the final R matrix to outputFile
    for (int i = 0; i < numberOfMatrices * MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            fprintf(outputFile, "%d ", R[i][j]);
        }
        fprintf(outputFile, "\n");
    }

    // Clean up and close file
    free(R);
    fclose(outputFile);

    return 0;
}