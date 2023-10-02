//
// Created by Sanjana Nagwekar on 9/11/23.
//
//
#include <stdio.h>
#include <stdlib.h>


#define ROWS_A 1
#define COLS_A 3
#define ROWS_W 3
#define COLS_W 5
#define ROWS_B 1
#define COLS_B 5

// Function to read a matrix from a file
void readMatrixFromFile(const char *filename, int rows, int cols, int matrix[rows][cols]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        fprintf(stderr, "Failed to open file: %s\n", filename);
        return; // Return without creating the matrix
    }

    int value;
    int check = 0;

    for (int row = 0; row < rows; row++) {
        check = 0;
        for (int col = 0; col < cols; col++) {
            //printf("col %d\n",col);
            if ((fscanf(file, "%d", &value) == 1)) {
                matrix[row][col] = value;
                check = check + 1;
            } else {
                matrix[row][col] = 0;
            }
            int c = fgetc(file);
            if (c == '\n' || c == EOF) {
                break;
            }
            ungetc(c, file);
        }
    }
    if (check < cols){
        for (int i = check; i<cols; i++){
            matrix[rows-1][i] = 0;
        }
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <matrix_A_file> <matrix_W_file> <matrix_B_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int matrixA[ROWS_A][COLS_A];
    int matrixB[ROWS_B][COLS_B];
    int matrixW[ROWS_W][COLS_W];
    int R[ROWS_A][COLS_B];


    readMatrixFromFile(argv[1], ROWS_A, COLS_A, matrixA);
    readMatrixFromFile(argv[2], ROWS_W, COLS_W, matrixW);
    readMatrixFromFile(argv[3], ROWS_B, COLS_B, matrixB);

    printf("Matrix A:\n");
    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_A; j++) {
            printf(" %d ", matrixA[i][j]);
        }
        printf("\n");
    }

    printf("Matrix W:\n");
    for (int i = 0; i < ROWS_W; i++) {
        for (int j = 0; j < COLS_W; j++) {
            printf(" %d ", matrixW[i][j]);
        }
        printf("\n");
    }

    printf("Matrix B:\n");
    for (int i = 0; i < ROWS_B; i++) {
        for (int j = 0; j < COLS_B; j++) {
            printf(" %d ", matrixB[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            R[i][j] = 0;
            for (int k = 0; k < COLS_A; k++) {
                R[i][j] += matrixA[i][k] * matrixW[k][j];
            }
            R[i][j] += matrixB[i][j];
        }
    }

    printf("Result of %s*%s+%s = [", argv[1], argv[2], argv[3]);
    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            printf(" %d ", R[i][j]);
        }
    }
    printf("]\n");

    return 0;
}