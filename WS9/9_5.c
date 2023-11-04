//
// Created by Sanjana Nagwekar on 11/4/23.
//
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void trimSpaces(char *str) {
    int len = strlen(str);
    int start = 0, end = len - 1;

    while (start < len && isspace(str[start])) {
        start++;
    }

    while (end >= start && isspace(str[end])) {
        end--;
    }

    for (int i = 0; i <= end - start; i++) {
        str[i] = str[start + i];
    }

    str[end - start + 1] = '\0';
}

int main(void) {

    /* Type your code here. */
    char input[50];

    while (1) {
        printf("Enter input string:\n");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        if (strcmp(input, "q") == 0) {
            break;
        }

        char *comma = strchr(input, ',');
        if (comma == NULL) {
            printf("Error: No comma in string.\n");
        } else {
            *comma = '\0';
            char *first_word = input;
            char *second_word = comma + 1;

            trimSpaces(first_word);
            trimSpaces(second_word);

            printf("First word: %s\nSecond word: %s\n", first_word, second_word);
        }
        printf("\n");
    }

    return 0;
}