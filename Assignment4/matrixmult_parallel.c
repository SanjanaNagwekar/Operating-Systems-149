//
// Created by Sanjana Nagwekar on 11/1/23.
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
        exit(EXIT_FAILURE);
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

int main(int argc, char *argv[]) {
    struct timespec start, finish;
    clock_gettime(CLOCK_MONOTONIC, &start);
    printf("start %ld\n", start.tv_sec);

    if (argc < 3 || argc > 10) {
        fprintf(stderr, "Usage: %s <matrix_A_file> <matrix_W1_file> <matrix_W2_file> ... <matrix_W8_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *matrixAFile = argv[1];

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

    // Create child processes for matrix multiplication
    for (int i = 2; i < argc; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            // Declare matrixA and matrixW in the child process
            int matrixA[MATRIX_SIZE][MATRIX_SIZE] = {0};
            readMatrixFromFile(argv[1], MATRIX_SIZE, MATRIX_SIZE, matrixA);

            int matrixW[MATRIX_SIZE][MATRIX_SIZE] = {0};
            readMatrixFromFile(argv[i], MATRIX_SIZE, MATRIX_SIZE, matrixW);

            // Pass the shared memory address to the child process
            int (*childR)[MATRIX_SIZE] = shmat(shared, NULL, 0);
            if (childR == (int (*)[MATRIX_SIZE])-1) {
                perror("shmat failed in child process");
                exit(EXIT_FAILURE);
            }

            // Matrix multiplication
            for (int j = 0; j < MATRIX_SIZE; j++) {
                for (int k = 0; k < MATRIX_SIZE; k++) {
                    childR[j][k] += matrixA[j][k] * matrixW[k][j];
                }
            }

            // Detach shared memory in child process
            shmdt(childR);

            exit(EXIT_SUCCESS);
        } else if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all child processes to complete
    for (int i = 2; i < argc; i++) {
        int status;
        wait(&status);
    }

    // Display the result matrix
    printf("Result of A*W = [\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%2d ", R[i][j]);
        }
        printf("\n");
    }
    printf("]\n");

    // Detach and remove shared memory segment
    shmdt(R);
    shmctl(shared, IPC_RMID, NULL);

    clock_gettime(CLOCK_MONOTONIC, &finish);
    double elapsed = (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Runtime %.4f seconds\n", elapsed);

    return 0;
}
