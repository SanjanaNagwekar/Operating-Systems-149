//
// Created by Sanjana Nagwekar on 10/11/23.
/*
 * File:   matrixmult_parallel.c
 * Date:   October 19, 2023
 */

//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <time.h>

#define MATRIX_SIZE 8

// Function to read a matrix from a file
void readMatrixFromFile(const char *filename, int rows, int cols, int matrix[rows][cols]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        fprintf(stderr, "Failed to open file: %s\n", filename);
        return;
    }

    char line[1024];

    for (int row = 0; row < rows; row++) {
        if (fgets(line, sizeof(line), file) == NULL) {
            break;
        }
        char *token = strtok(line, " \t");
        for (int col = 0; col < cols; col++) {
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
/*
int dotProduct(int vectorA[], int vectorB[], int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        result += vectorA[i] * vectorB[i];
    }
    return result;
}
 */

int main(int argc, char *argv[]) {

    struct timespec start, finish;
    clock_gettime(CLOCK_MONOTONIC, &start);
    printf("start %ld\n", start.tv_sec);


    if (argc != 3) {
        fprintf(stderr, "Usage: %s <matrix_A_file> <matrix_W_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int matrixA[MATRIX_SIZE][MATRIX_SIZE] = {0};
    int matrixW[MATRIX_SIZE][MATRIX_SIZE] = {0};

    // Read input files A and W
    readMatrixFromFile(argv[1], MATRIX_SIZE, MATRIX_SIZE, matrixA);
    readMatrixFromFile(argv[2], MATRIX_SIZE, MATRIX_SIZE, matrixW);

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

    // Method implemented: creating shared memory
    key_t key = ftok("matrixmult_parallel.c", 1);
    int shared = shmget(key, sizeof(int[MATRIX_SIZE][MATRIX_SIZE]), IPC_CREAT | 0666);
    if (shared == -1) {
        perror("shmget() failed");
        exit(EXIT_FAILURE);
    }

    int (*R)[MATRIX_SIZE] = shmat(shared, NULL, 0);

    if (R == (int (*)[MATRIX_SIZE])-1) {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    // Creating child processes
    for (int i = 0; i < MATRIX_SIZE; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Calculate result matrix
            for (int j = 0; j < MATRIX_SIZE; j++) {
                for (int k = 0; k < MATRIX_SIZE; k++) {
                    R[i][j] += matrixA[i][k] * matrixW[k][j];
                }
            }
            exit(EXIT_SUCCESS);
        } else if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
    }

    // Parent process waits for completion of child processes
    for (int i = 0; i < MATRIX_SIZE; i++) {
        wait(NULL);
    }

    printf("Result of A*W = [\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%2d ", R[i][j]);
        }
        printf("\n");
    }
    printf("]\n");
    printf("\n");

    shmdt(R);
    shmctl(shared, IPC_RMID, NULL);

    clock_gettime(CLOCK_MONOTONIC, &finish);
    double elapsed = (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Runtime %.4f seconds\n", elapsed);

    return 0;

}