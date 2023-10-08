//
// Created by Sanjana Nagwekar on 10/7/23.
//
#include <stdio.h>
#include <stdbool.h>

/* Define your function here */
bool IsArrayMult10(int inputVals[], int numVals) {
    for (int i = 0; i < numVals; i++) {
        if (inputVals[i] % 10 != 0)
            return false;
    }
    return true;
}

bool IsArrayNoMult10(int inputVals[], int numVals) {
    for (int i = 0; i < numVals; i++) {
        if (inputVals[i] % 10 == 0)
            return false;
    }
    return true;
}

int main(void) {
    /* Type your code here. Remember to include the bool library */
    int count = 0;
    int vals[20];

    do {
        scanf("%d", &vals[count++]);
    } while (getchar() != '\n' && count < 20); // Limit the input to 20 values


    int num = vals[0];
    int arr[num];
    for (int i = 1; i <= num; i++) {
        arr[i - 1] = vals[i];
    }

    if (IsArrayMult10(arr, num))
        printf("all multiples of 10\n");
    else if (IsArrayNoMult10(arr, num))
        printf("no multiples of 10\n");
    else
        printf("mixed values\n");

    return 0;
}
