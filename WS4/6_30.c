//
// Created by Sanjana Nagwekar on 9/23/23.
//
#include <stdio.h>

/* Define your function here */
int MaxNumber(int num1, int num2, int num3, int num4){
    if(num1 >= num2 && num1 >= num3 && num1 >= num4)
        return num1;
    else if(num2 >= num1 && num2 >= num3 && num2>= num4)
        return num2;
    else if(num3 >= num1 && num3 >= num2 && num3>= num4)
        return num3;
    return num4;
}

int MinNumber(int num1, int num2, int num3, int num4){
    if(num1 <= num2 && num1 <= num3 && num1 <= num4)
        return num1;
    else if(num2 <= num1 && num2 <= num3 && num2 <= num4)
        return num2;
    else if(num3 <= num1 && num3 <= num2 && num3 <= num4)
        return num3;
    return num4;
}

int main(void) {

    /* Type your code here. Your code must call the function.  */
    int num1;
    int num2;
    int num3;
    int num4;

    scanf("%d", &num1);
    scanf("%d", &num2);
    scanf("%d", &num3);
    scanf("%d", &num4);

    printf("Maximum is %d\n", MaxNumber(num1,num2,num3,num4));
    printf("Minimum is %d\n", MinNumber(num1,num2,num3,num4));

    return 0;
}
