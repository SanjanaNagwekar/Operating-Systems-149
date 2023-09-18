//
// Created by Sanjana Nagwekar on 9/18/23.
//
#include <stdio.h>

int main(void) {
    int small;
    int smallest;

    int n;
    int val;

    scanf("%d", &n);

    scanf("%d", &val);
    smallest = val;

    scanf("%d", &val);
    if(val < smallest){
        small = smallest;
        smallest = val;
    }
    else
        small = val;

    for(int i = 2; i<n; i++){
        scanf("%d", &val);
        if(val < smallest){
            small = smallest;
            smallest = val;
        }else if (val < small){
            small = val;
        }
    }

    printf("%d and %d\n", smallest, small);

    return 0;
}
