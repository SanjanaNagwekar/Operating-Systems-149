//
// Created by Sanjana Nagwekar on 9/18/23.
//
#include <stdio.h>

int main(void) {
    const int NUM_ELEMENTS = 20;
    int userValues[NUM_ELEMENTS];    // Set of data specified by the user

    /* Type your code here. */
    int n;
    int val;
    scanf("%d", &n);
    for(int i = 0; i<n; i++){
        scanf("%d", &val);
        userValues[i] = val;
    }
    int max;
    scanf("%d", &max);

    for(int i = 0; i<n; i++){
        if(userValues[i] < max)
            printf("%d,", userValues[i]);
    }

    printf("\n");

    return 0;
}
