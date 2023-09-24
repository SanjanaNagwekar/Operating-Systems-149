//
// Created by Sanjana Nagwekar on 9/23/23.
//
#include <stdio.h>

/* Define your function here */
double LapsToMiles(double userLaps){
    return (0.25*userLaps);
}

int main(void) {

    /* Type your code here. Your code must call the function.  */
    double laps;
    scanf("%lf", &laps);
    printf("%0.2lf\n", LapsToMiles(laps));

    return 0;
}
