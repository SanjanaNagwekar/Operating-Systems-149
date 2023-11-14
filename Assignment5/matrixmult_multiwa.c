//
// Created by Sanjana Nagwekar on 11/13/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_FILENAME_LENGTH 100
#define MAX_MATRICES 12

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <A_matrix_filename_placeholder> <W_matrix_filename1> [<W_matrix_filename2> ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int numWMatrices = argc - 2;
    int pipes[numWMatrices][2];

    // Create pipes and fork child processes
    for (int i = 0; i < numWMatrices; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) { // Child process
            close(pipes[i][1]); // Close write-end of the pipe

            // Redirect stdin to read from the pipe
            if (dup2(pipes[i][0], STDIN_FILENO) == -1) {
                perror("dup2");
                exit(EXIT_FAILURE);
            }

            execl("./matrixmult_parallel", "matrixmult_parallel", argv[i + 2], (char *)NULL);
            perror("execl");
            exit(EXIT_FAILURE);
        } else {
            close(pipes[i][0]); // Close read-end of the pipe in parent
        }
    }
    // Parent process: Read A matrix filenames from stdin and send to children
    char filename[MAX_FILENAME_LENGTH];
    while (1) {
        printf("Waiting for A matrix filename...\n");  // Debugging statement

        if (!fgets(filename, MAX_FILENAME_LENGTH, stdin)) {
            if (feof(stdin)) {
                printf("EOF reached. Sending termination signals to child processes.\n");
                break; // Exit loop on EOF
            } else {
                perror("Error reading from stdin");
                break; // Exit loop on error
            }
        }

        filename[strcspn(filename, "\n")] = 0; // Remove newline character
        printf("Read filename: '%s'\n", filename); // Debugging statement

        for (int i = 0; i < numWMatrices; i++) {
            printf("Sending filename '%s' to child process %d\n", filename, i); // Debugging statement
            if (write(pipes[i][1], filename, strlen(filename) + 1) == -1) {
                perror("write");
            }
        }
    }

    // Send termination signal (e.g., empty string) to children
    strcpy(filename, ""); // Set filename to empty string as termination signal
    for (int i = 0; i < numWMatrices; i++) {
        ssize_t bytesWritten = write(pipes[i][1], filename, strlen(filename) + 1);
        if (bytesWritten == -1) {
            perror("write");
        } else {
            printf("Sent termination signal to child process %d\n", i);
        }
        close(pipes[i][1]); // Close write-end of the pipe after sending termination signal
    }


    // Wait for all child processes to finish
    int status;
    for (int i = 0; i < numWMatrices; i++) {
        pid_t childPid = wait(&status);
        if (childPid == -1) {
            perror("wait");
        } else {
            if (WIFEXITED(status)) {
                printf("Child with PID %d exited with status %d\n", childPid, WEXITSTATUS(status));
            }
        }
    }
    return 0;
}