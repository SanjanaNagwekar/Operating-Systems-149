//
// Created by Sanjana Nagwekar on 10/15/23.
//
#include <stdio.h>

/* Define your function here */
void SwapValues(int* userVal1, int* userVal2, int* userVal3, int* userVal4) {
    int temp;
    temp = *userVal1;
    *userVal1 = *userVal2;
    *userVal2 = temp;

    temp = *userVal3;
    *userVal3 = *userVal4;
    *userVal4 = temp;
}

int main(void) {
    /* Type your code here. Your code must call the function. */
    int vals[4];
    int n;

    for (int i = 0; i < 4; i++) {
        scanf("%d", &n);
        vals[i] = n;
    }

    SwapValues(&vals[0], &vals[1], &vals[2], &vals[3]);
    printf("%d %d %d %d\n", vals[0], vals[1], vals[2], vals[3]);

    return 0;
}
