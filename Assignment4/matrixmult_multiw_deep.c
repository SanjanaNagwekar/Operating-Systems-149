//
// Created by Sanjana Nagwekar on 11/1/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>


#define MATRIX_SIZE 8
#define MAX_MATRIX_FILES 10

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
void handleChildTermination(int status) {
    if (WIFEXITED(status)) {
        fprintf(stderr, "Exited with exitcode = %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        fprintf(stderr, "Killed with signal %d\n", WTERMSIG(status));
    }
}

// Function to execute matrix multiplication in parallel
void executeMatrixMultParallel(const char *matrixAFile, const char *matrixWFile, int index, int R[MATRIX_SIZE][MATRIX_SIZE]) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        close(pipefd[0]); // Close unused read end of the pipe

        // Redirect stdout to the pipe
        dup2(pipefd[1], STDOUT_FILENO);

        // Open a file for writing the child process output
        char outputFileName[20];
        sprintf(outputFileName, "%d.out", getpid());
        int outputFile = open(outputFileName, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (outputFile == -1) {
            perror("Error opening output file");
            exit(EXIT_FAILURE);
        }

        // Redirect stdout to the file
        dup2(outputFile, STDOUT_FILENO);
        close(outputFile); // Close the file descriptor, as dup2 duplicates it

        // Redirect stderr to the file
        char errorFileName[20];
        sprintf(errorFileName, "%d.err", getpid());
        int errorFile = open(errorFileName, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (errorFile == -1) {
            perror("Error opening error file");
            exit(EXIT_FAILURE);
        }
        dup2(errorFile, STDERR_FILENO);
        close(errorFile); // Close the file descriptor, as dup2 duplicates it

        signal(SIGTERM, SIG_DFL);

        execlp("./matrixmult_parallel", "matrixmult_parallel", matrixAFile, matrixWFile, (char *)NULL);

        perror("Exec failed");
        exit(EXIT_FAILURE);
    }
}
int main(int argc, char *argv[]) {
    // Check if command line arguments are sufficient
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <matrix_A_file> <matrix_W1_file> <matrix_W2_file> ... <matrix_WN_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *matrixAFile = argv[1];
    int Rsum[MATRIX_SIZE][MATRIX_SIZE] = {0};

    // Read and process W matrices from command-line arguments
    for (int i = 2; i < argc; i++) {
        executeMatrixMultParallel(matrixAFile, argv[i], i - 2, Rsum);
    }

    // Read and process additional lines of W matrices from stdin
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, stdin)) != -1) {
        char **wFiles = malloc(MAX_MATRIX_FILES * sizeof(char *));
        int wCount = 0;

        char *token = strtok(line, " \t");
        while (token != NULL) {
            wFiles[wCount++] = strdup(token);
            token = strtok(NULL, " \t");
        }

        for (int i = 0; i < wCount; i++) {
            executeMatrixMultParallel(matrixAFile, wFiles[i], -1, Rsum);
            free(wFiles[i]);
        }

        free(wFiles);
    }

    free(line);

    // Print the final Rsum matrix to stdout
    printf("Rsum = [");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        printf(" %d", Rsum[i][0]);
        for (int j = 1; j < MATRIX_SIZE; j++) {
            printf(" %d", Rsum[i][j]);
        }
        if (i < MATRIX_SIZE - 1) {
            printf(" \n");
        }
    }
    printf("]\n");

    FILE *pidOut = fopen("PID.out", "w");
    if (pidOut == NULL) {
        perror("Error opening PID.out");
        exit(EXIT_FAILURE);
    }

    fprintf(pidOut, "Finished child PID %d of parent PPID %d\n", getpid(), getppid());
    fclose(pidOut);

    return 0;
}
