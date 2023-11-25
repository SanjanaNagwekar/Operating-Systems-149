//
// Created by Sanjana Nagwekar on 11/24/23.
//
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *data = (int*)malloc(sizeof(int) * 100);

    if (data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    free(data);

    printf("%d\n", data[50]);

    return 0;
}