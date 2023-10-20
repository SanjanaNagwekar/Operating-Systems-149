#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <time.h>

#define MAX_MATRIX_FILES 10
#define MATRIX_SIZE 8

void executeMatrixMultParallel(const char *matrixAFile, const char *matrixWFile, int index) {
    pid_t pid = fork();

    if (pid == 0) {
        char outputFileName[64];
        char errorFileName[64];

        // Create output and error file names for this child process
        snprintf(outputFileName, sizeof(outputFileName), "%d.out", getpid());
        snprintf(errorFileName, sizeof(errorFileName), "%d.err", getpid());

        int out = open(outputFileName, O_RDWR | O_CREAT | O_APPEND, 0777);
        int err = open(errorFileName, O_RDWR | O_CREAT | O_APPEND, 0777);

        if (out == -1 || err == -1) {
            perror("Error opening output or error file");
            exit(EXIT_FAILURE);
        }

        // Redirect stdout and stderr to the output and error files
        dup2(out, 1);
        dup2(err, 2);

        printf("Starting command %d: child %d pid of parent %d\n", index + 1, getpid(), getppid());
        fflush(stdout);

        // Execute matrixmult_parallel with matrixAFile and matrixWFile
        execlp("./matrixmult_parallel", "matrixmult_parallel", matrixAFile, matrixWFile, (char *) NULL);

        // If exec fails, exit with an error code
        perror("Exec failed");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else {
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Child %d exited with exitcode = %d\n", pid, WEXITSTATUS(status));
            fflush(stdout);
        } else if (WIFSIGNALED(status)) {
            printf("Child %d killed with signal %d\n", pid, WTERMSIG(status));
            fflush(stdout);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3 || argc > (MAX_MATRIX_FILES + 2)) {
        fprintf(stderr, "Usage: %s <matrix_A_file> <matrix_W1_file> <matrix_W2_file> ... <matrix_WN_file>\n", argv[0]);
        fflush(stdout);
        exit(EXIT_FAILURE);
    }

    const char *matrixAFile = argv[1];

    for (int i = 2; i < argc; i++) {
        executeMatrixMultParallel(matrixAFile, argv[i], i - 2);
    }

    return 0;
}
