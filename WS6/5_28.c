//
// Created by Sanjana Nagwekar on 10/7/23.
//
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_palindrome(char *str) {
    int left = 0;
    int right = strlen(str) - 1;
    while (left < right) {
        while (!isalnum(str[left]) && left < right) {
            left++;
        }
        while (!isalnum(str[right]) && left < right) {
            right--;
        }
        if (tolower(str[left]) != tolower(str[right])) {
            return 0; // Not a palindrome
        }
        left++;
        right--;
    }
    return 1;
}

int main(void) {

    char str[50];
    fgets(str, sizeof(str), stdin);

    if (is_palindrome(str)) {
        printf("palindrome: %s\n", str);
    } else {
        printf("not a palindrome: %s\n", str);
    }

    return 0;
}
