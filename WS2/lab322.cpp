//
// Created by Sanjana Nagwekar on 9/11/23.
//
#include <stdio.h>

int main(void) {

    /* Type your code here. */
    int x;
    int y;
    int z;

    scanf("%d%d%d", &x, &y, &z);

    if(x<=y && x<=z)
        printf("%d\n", x);
    else if(y<=x && y<=z)
        printf("%d\n", y);
    else
        printf("%d\n", z);


    return 0;
}
