//
// Created by Sanjana Nagwekar on 10/23/23.
//
#include <stdio.h>
#include <string.h>

/* Define your function here */
int CalcNumCharacters(char* userString, char userChar){
    int count = 0;
    for(int i = 0; i< strlen(userString); i++){
        if(userString[i] == userChar)
            count++;
    }
    return count;
}

int main(void) {

    /* Type your code here. */
    char ch;
    scanf("%c", &ch);
    char str[50];
    fgets(str, sizeof(str), stdin);
    if (CalcNumCharacters(str, ch) == 1)
        printf("%d %c\n", CalcNumCharacters(str, ch), ch);
    else
        printf("%d %c's\n", CalcNumCharacters(str, ch), ch);

    return 0;
}
