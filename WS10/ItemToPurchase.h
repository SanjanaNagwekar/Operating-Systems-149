//
// Created by Sanjana Nagwekar on 11/11/23.
//
// ItemToPurchase.h
#ifndef CLASS1HANDS_ONWORKSHEET_ITEMTOPURCHASE_H
#define CLASS1HANDS_ONWORKSHEET_ITEMTOPURCHASE_H

typedef struct ItemToPurchase_struct {
    char itemName[20];
    int itemPrice;
    int itemQuantity;
} ItemToPurchase;

void MakeItemBlank(ItemToPurchase* item);
void PrintItemCost(ItemToPurchase item);

#endif