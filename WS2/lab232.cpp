//
// Created by Sanjana Nagwekar on 9/11/23.
//
#include <stdio.h>

int main(void) {
    int currentPrice;
    int lastMonthsPrice;

    scanf("%d", &currentPrice);
    scanf("%d", &lastMonthsPrice);

    /* Type your code here. */
    printf("%s%d%s%d%s\n", "This house is $", currentPrice, ". The change is $", currentPrice-lastMonthsPrice," since last month.");
    printf("%s%.6lf.\n","The estimated monthly mortgage is $", (currentPrice*0.051)/12);


    return 0;
}