//
// Created by Sanjana Nagwekar on 9/18/23.
//
#include <stdio.h>

int main(void) {
    const int NUM_ELEMENTS = 9;
    int userValues[NUM_ELEMENTS];    // Set of data specified by the user

    int count = 0;
    int val;
    scanf("%d", &val);

    while(val >= 0){
        userValues[count] = val;
        scanf("%d", &val);
        count+=1;
    }

    if(count > 9)
        printf("Too many numbers\n");
    else
        printf("Middle item: %d\n", userValues[count/2]);

    /* Type your code here. */


    return 0;
}
