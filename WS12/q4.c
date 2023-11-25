//
// Created by Sanjana Nagwekar on 11/24/23.
//
#include <stdlib.h>

int main() {
    int *ptr = (int*)malloc(sizeof(int) * 100); // Allocate memory for 100 integers.


    return 0; // Exiting the program without freeing the memory.
}