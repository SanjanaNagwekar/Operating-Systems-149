//
// Created by Sanjana Nagwekar on 9/18/23.
//
#include <stdio.h>

int main(void) {

    /* Type your code here. */
    int x;
    scanf("%d", &x);

    while(x>0){
        printf("%d",x % 2);
        x /= 2;
    }
    printf("\n");

    return 0;
}
