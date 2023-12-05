//
// Created by Sanjana Nagwekar on 12/4/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#define MATRIX_SIZE 8

pthread_mutex_t lock;
int matrixA[MATRIX_SIZE][MATRIX_SIZE];
int matrixW[MATRIX_SIZE][MATRIX_SIZE];
int matrixR[MATRIX_SIZE][MATRIX_SIZE];

// Function to read a matrix from a file
void readMatrixFromFile(const char *filename, int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        fprintf(stderr, "Failed to open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[1024];
    for (int row = 0; row < MATRIX_SIZE; row++) {
        if (fgets(line, sizeof(line), file) == NULL) {
            break;
        }
        char *token = strtok(line, " \t");
        for (int col = 0; col < MATRIX_SIZE; col++) {
            if (token != NULL) {
                matrix[row][col] = atoi(token);
                token = strtok(NULL, " \t");
            } else {
                matrix[row][col] = 0;
            }
        }
    }
    fclose(file);
}

// Thread function for matrix multiplication
void *multiplyRow(void *arg) {
    int row = *(int *)arg;
    for (int j = 0; j < MATRIX_SIZE; j++) {
        for (int k = 0; k < MATRIX_SIZE; k++) {
            matrixR[row][j] += matrixA[row][k] * matrixW[k][j];
        }
    }
    free(arg);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <matrix_A_file> <matrix_W_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Read matrices from files
    readMatrixFromFile(argv[1], matrixA);
    readMatrixFromFile(argv[2], matrixW);

    printf("Matrix A:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf(" %d ", matrixA[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Matrix W:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf(" %d ", matrixW[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    pthread_t threads[MATRIX_SIZE];
    pthread_mutex_init(&lock, NULL);

    // Creating threads for each row
    for (int i = 0; i < MATRIX_SIZE; i++) {
        int *arg = malloc(sizeof(*arg));
        if (arg == NULL) {
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }
        *arg = i;
        if (pthread_create(&threads[i], NULL, multiplyRow, arg) != 0) {
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }

    // Joining threads
    for (int i = 0; i < MATRIX_SIZE; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            exit(EXIT_FAILURE);
        }
    }

    pthread_mutex_destroy(&lock);

    // Printing the result
    printf("Result of A*W = [\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%2d ", matrixR[i][j]);
        }
        printf("\n");
    }
    printf("]\n");

    return 0;
}
