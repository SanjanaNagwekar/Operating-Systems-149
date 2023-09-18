//
// Created by Sanjana Nagwekar on 9/18/23.
//
#include <stdio.h>

int main(void) {

    /* Type your code here. */
    int count = 0;
    int sum = 0;
    int x = 0;
    int max = 0;
    scanf("%d", &x);

    while(x >= 0){
        count+=1;
        sum+=x;
        if(x > max)
            max = x;
        scanf("%d", &x);
    }
    printf("%d %0.2lf\n", max, (double) sum/count);

    return 0;
}
