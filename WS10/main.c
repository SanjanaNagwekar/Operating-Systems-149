//
// Created by Sanjana Nagwekar on 11/11/23.
//
#include<stdio.h>
#include<string.h>

#include "ItemToPurchase.h"

int main(void) {
    char c;
    char name[20];
    int price;
    int quant;

    // Item 2
    printf("Item 1\n");
    ItemToPurchase item1;

    printf("Enter the item name:\n");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove the newline character

    printf("Enter the item price:\n");
    scanf("%d", &price);

    printf("Enter the item quantity:\n");
    scanf("%d", &quant);

    strcpy(item1.itemName, name);
    item1.itemPrice = price;
    item1.itemQuantity = quant;

    // Clear the input buffer
    c = getchar();
    while(c != '\n' && c != EOF) {
        c = getchar();
    }

    // Item 2
    printf("\nItem 2\n");
    ItemToPurchase item2;

    printf("Enter the item name:\n");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Enter the item price:\n");
    scanf("%d", &price);

    printf("Enter the item quantity:\n");
    scanf("%d", &quant);

    strcpy(item2.itemName, name);
    item2.itemPrice = price;
    item2.itemQuantity = quant;

    //Print totals

    printf("\nTOTAL COST\n");
    PrintItemCost(item1);
    PrintItemCost(item2);
    printf("\nTotal: $%d\n", (item1.itemPrice * item1.itemQuantity) + (item2.itemPrice * item2.itemQuantity));

    return 0;
}