//
// Created by Sanjana Nagwekar on 9/11/23.
//
#include <stdio.h>
#include <math.h>

int main(void) {
    double x;
    double y;
    double z;

    scanf("%lf%lf%lf", &x, &y, &z);

    printf("%.2lf %.2lf %.2lf %.2lf\n", pow(x,z), pow(x,pow(y,2)), fabs(y), sqrt(pow(x*y,z)));

    /* Type your code here. Note: Include the math library above first. */

    return 0;
}
