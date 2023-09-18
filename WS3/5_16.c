//
// Created by Sanjana Nagwekar on 9/18/23.
//
#include <stdio.h>

int main(void) {
    const int NUM_ELEMENTS = 20;         // Number of input integers
    int userVals[NUM_ELEMENTS];          // Array to hold the user's input integers

    /* Type your code here. */
    int n;
    int val;
    scanf("%d", &n);
    for(int i = 0; i<n; i++){
        scanf("%d", &val);
        userVals[i] = val;
    }
    for(int i = n-1; i>=0; i--){
        printf("%d,", userVals[i]);
    }

    printf("\n");
    return 0;
}
