//
// Created by Sanjana Nagwekar on 10/2/23.
//
#include <stdio.h>
#include <string.h>

int main(void) {

    /* Type your code here. */
    char str[50];
    fgets(str, 50, stdin);
    int count = 0;
    for(int i = 0; i< strlen(str); i++){
        if(!(str[i] == ' ' || str[i] == '.' || str[i] == ',' || str[i] == '!'))
            count++;
    }
    printf("%d\n", count);

    return 0;
}
