//
// Created by Sanjana Nagwekar on 9/23/23.
//

#include <stdio.h>
#include <string.h>

int main(void) {

    /* Type your code here. */
    int n;
    scanf("%d", &n);

    char words[20][11];
    char word[11];
    for (int i = 0; i < n; ++i) {
        scanf("%s", &word);
        strcpy(words[i], word);
    }

    char cont;
    scanf(" %c", &cont);

    for(int i = 0; i< n; i++){
        if (strchr(words[i], cont) != NULL) {
            printf("%s,", words[i]);
        }
    }
    printf("\n");
    return 0;
}
