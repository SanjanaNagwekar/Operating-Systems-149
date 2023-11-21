//
// Created by Sanjana Nagwekar on 11/20/23.
//

#include <stdio.h>
#include <string.h>

typedef struct ContactNode_struct {
    char contactName[50];
    char contactPhoneNumber[50];
    struct ContactNode_struct* nextNodePtr;
} ContactNode;

void InitializeContactNode(ContactNode* node, char fullName[], char phoneNum[]) {
    strcpy(node->contactName, fullName);
    strcpy(node->contactPhoneNumber, phoneNum);
    node->nextNodePtr = NULL;
}

void InsertAfter(ContactNode* insertAfter, ContactNode* nodeToInsert) {
    if (insertAfter != NULL) {
        nodeToInsert->nextNodePtr = insertAfter->nextNodePtr;
        insertAfter->nextNodePtr = nodeToInsert;
    }
}
void PrintContactNode(ContactNode* node, int personNum) {
    printf("Person %d: %s, %s\n", personNum, node->contactName, node->contactPhoneNumber);
}

ContactNode* GetNext(ContactNode* node) {
    return (node != NULL) ? node->nextNodePtr : NULL;
}

char* GetName(ContactNode* node) {
    return node->contactName;
}

char* GetPhoneNumber(ContactNode* node) {
    return node->contactPhoneNumber;
}

int main(void) {
    ContactNode contact1, contact2, contact3;
    char name[50];
    char phoneNum[50];

    // Contact1
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; // Remove newline character
    fgets(phoneNum, sizeof(phoneNum), stdin);
    phoneNum[strcspn(phoneNum, "\n")] = 0;
    InitializeContactNode(&contact1, name, phoneNum);

    // Contact2
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    fgets(phoneNum, sizeof(phoneNum), stdin);
    phoneNum[strcspn(phoneNum, "\n")] = 0;
    InitializeContactNode(&contact2, name, phoneNum);


    InsertAfter(&contact1, &contact2);

    // Contact3
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    fgets(phoneNum, sizeof(phoneNum), stdin);
    phoneNum[strcspn(phoneNum, "\n")] = 0;
    InitializeContactNode(&contact3, name, phoneNum);


    InsertAfter(&contact2, &contact3);

    ContactNode* currentNode = &contact1;
    int personNum = 1;

    while (currentNode != NULL) {
        PrintContactNode(currentNode, personNum++);
        currentNode = GetNext(currentNode);
    }

    // Print "CONTACT LIST"
    printf("\nCONTACT LIST");
    currentNode = &contact1; // Reset to the start of the list
    while (currentNode != NULL) {
        printf("\nName: %s\nPhone number: %s\n", currentNode->contactName, currentNode->contactPhoneNumber);
        currentNode = GetNext(currentNode);
    }
    printf("\n");

    return 0;
}
