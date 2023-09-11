//
// Created by Sanjana Nagwekar on 9/11/23.
//
#include <stdio.h>

int main(void) {

    /* Type your code here. */
    int userNum;
    int divNum;

    scanf("%d%d", &userNum, &divNum);

    for(int i = 0; i<2; i++){
        printf("%d ", userNum/divNum);
        userNum /= divNum;
    }
    printf("%d\n", userNum/divNum);
    return 0;
}
