//
// Created by Sanjana Nagwekar on 9/18/23.
//
#include <stdio.h>

int main(void) {

    /* Type your code here. */
    int n;
    scanf("%d", &n);
    int vals[n];
    int val;

    for(int i= 0; i < n; i++){
        scanf("%d", &val);
        vals[i] = val;
    }
    int min;
    int max;
    scanf("%d", &min);
    scanf("%d", &max);

    for(int i = 0; i<n; i++){
        if(vals[i] >= min && vals[i] <= max)
            printf("%d,", vals[i]);
    }
    printf("\n");
    return 0;
}
