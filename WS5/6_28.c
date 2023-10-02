//
// Created by Sanjana Nagwekar on 10/2/23.
//
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Define your function here */
void RemoveNonAlpha(char userString[], char userStringAlphaOnly[]) {
    int count = 0;
    for (int i = 0; i < strlen(userString); i++) {
        if ((userString[i] >= 'A' && userString[i] <= 'Z') || (userString[i] >= 'a' && userString[i] <= 'z')) {
            userStringAlphaOnly[count] = userString[i];
            count++;
        }
    }
    userStringAlphaOnly[count] = '\0';
}

int main(void) {

    /* Type your code here. */
    char userString[50];
    fgets(userString, 50, stdin);

    char userStringAlphaOnly[50];
    RemoveNonAlpha(userString, userStringAlphaOnly);

    printf("%s\n", userStringAlphaOnly);

    return 0;
}