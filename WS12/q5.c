//
// Created by Sanjana Nagwekar on 11/24/23.
//
#include <stdlib.h>

int main() {
    int *data = (int*)malloc(sizeof(int) * 100); // Allocate memory for 100 integers.

    if (data == NULL) {
        return 1;
    }

    data[100] = 0;

    free(data);

    return 0;
}