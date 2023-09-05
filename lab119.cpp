//
// Created by Sanjana Nagwekar on 9/4/23.
//
#include <stdio.h>

int main(void) {
    int userNum;

    printf("Enter integer:\n");
    scanf("%d", &userNum);

    printf("%s %d\n", "You entered:", userNum);
    /* Type your code here. */

    printf("%d %s %d\n", userNum, "squared is", userNum*userNum);
    printf("%s %d %s %d%s\n", "And", userNum, "cubed is", userNum*userNum*userNum, "!!");

    int userNum2;
    printf("Enter another integer:\n");
    scanf("%d", &userNum2);

    printf("%d%s%d%s%d\n", userNum, " + ", userNum2, " is ", userNum+userNum2);
    printf("%d%s%d%s%d\n", userNum, " * ", userNum2, " is ", userNum*userNum2);

    return 0;
}