//
// Created by Sanjana Nagwekar on 12/2/23.
//
// BONUS OPTION 7 (EXPAND ASSIGNMENT 1)


/* SAMPLE OUTPUT
 * /Users/sanjananagwekar/CLionProjects/cs149/matrixmult A1.txt W1.txt B1.txt C1.txt

 Matrix A:
 10  30  40
Matrix W:
 1  3  4  5  1
 2  4  5  1  1
 5  0  0  0  0
Matrix B:
 1  1  1  1  1
Correct Vector:
 5 4 3 2 1
Closest matrix index: 0
Filename of weight matrix: W1.txt
Result vector: [ 271  151  191  81  41 ]
Cosine: 0.982246

Process finished with exit code 0
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS_A 1
#define COLS_A 3
#define ROWS_W 3
#define COLS_W 5
#define ROWS_B 1
#define COLS_B 5

// Function to read a vector from a file
void readVectorFromFile(const char *filename, int size, int vector[size]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        fprintf(stderr, "Failed to open file: %s\n", filename);
        return;
    }

    for (int i = 0; i < size; i++) {
        if (fscanf(file, "%d", &vector[i]) != 1) {
            vector[i] = 0;
        }
    }

    fclose(file);
}

// Function to compute cosine distance between two vectors
double cosineDistance(const int vec1[], const int vec2[], int size) {
    double dot = 0.0, normVec1 = 0.0, normVec2 = 0.0;
    for (int i = 0; i < size; i++) {
        dot += vec1[i] * vec2[i];
        normVec1 += vec1[i] * vec1[i];
        normVec2 += vec2[i] * vec2[i];
    }
    double magnitude = sqrt(normVec1) * sqrt(normVec2);
    if (magnitude == 0) {
        return 2.0; // Return a large number if one of the vectors is zero
    }
    return dot / magnitude;
}

void readMatrixFromFile(const char *filename, int rows, int cols, int matrix[rows][cols]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        fprintf(stderr, "Failed to open file: %s\n", filename);
        return;
    }

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (fscanf(file, "%d", &matrix[row][col]) != 1) {
                matrix[row][col] = 0; // Fill in 0 if no value is read
            }
        }
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <matrix_A_file> <matrix_W_file> <matrix_B_file> <correct_vector_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int matrixA[ROWS_A][COLS_A] = {{0}};
    int matrixB[ROWS_B][COLS_B] = {{0}};
    int matrixW[ROWS_W][COLS_W] = {{0}};
    int R[ROWS_A][COLS_B] = {{0}};
    int correctVector[COLS_B] = {0};

    readMatrixFromFile(argv[1], ROWS_A, COLS_A, matrixA);
    readMatrixFromFile(argv[2], ROWS_W, COLS_W, matrixW);
    readMatrixFromFile(argv[3], ROWS_B, COLS_B, matrixB);
    readVectorFromFile(argv[4], COLS_B, correctVector);

    double minDistance = 2.0; // Cosine distance ranges from -1 to 1
    int minIndex = -1;
    int bestR[COLS_B]; // To store the best result vector

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

    printf("Correct Vector:\n");
    for (int i = 0; i < COLS_B; i++) {
        printf(" %d", correctVector[i]);
    }
    printf("\n");

    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            R[i][j] = 0;
            for (int k = 0; k < COLS_A; k++) {
                R[i][j] += matrixA[i][k] * matrixW[k][j];
            }
            R[i][j] += matrixB[i][j];
        }
    }
    for (int i = 0; i < ROWS_A; i++) {
        double distance = cosineDistance(R[i], correctVector, COLS_B);
        if (distance < minDistance) {
            minDistance = distance;
            minIndex = i;
            for (int j = 0; j < COLS_B; j++) {
                bestR[j] = R[i][j];
            }
        }
    }

    if (minIndex != -1) {
        printf("Closest matrix index: %d\n", minIndex);
        printf("Filename of weight matrix: %s\n", argv[2]);
        printf("Result vector: [");
        for (int j = 0; j < COLS_B; j++) {
            printf(" %d ", bestR[j]);
        }
        printf("]\n");
        printf("Cosine: %f\n", minDistance);
    } else {
        printf("No closest matrix found.\n");
    }

    return 0;
}