#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "library/project.h"

int main(void) {
    struct Message original;
    struct Message working;
    char subKey[27] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    char reverseKey[26];
    int choice;
    int key;

    printf("=== MESSAGE INPUT ===\n");
    inputMessage(&original);
    working = original;   // copy for manipulation

    while (1) {
        printf("\n=== MENU ===\n");
        printf("1. Display message\n");
        printf("2. Caesar encrypt\n");
        printf("3. Caesar decrypt\n");
        printf("4. XOR encrypt/decrypt\n");
        printf("5. Substitution encrypt\n");
        printf("6. Substitution decrypt\n");
        printf("7. Reverse message\n");
        printf("8. Remove spaces\n");
        printf("9. Frequency analysis\n");
        printf("10. Index of Coincidence\n");
        printf("11. Reset message\n");
        printf("0. Exit\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1) break;
        getchar(); // consume newline

        switch (choice) {

        case 1:
            displaymessage(&working);
            break;

        case 2:
            printf("Enter Caesar key: ");
            scanf("%d", &key);
            getchar();
            encryptCesar(&working, key);
            displaymessage(&working);
            break;

        case 3:
            printf("Enter Caesar key: ");
            scanf("%d", &key);
            getchar();
            decryptCesar(&working, key);
            displaymessage(&working);
            break;

        case 4:
            printf("Enter XOR key (0–255): ");
            scanf("%d", &key);
            getchar();
            encryptXOR(&working, key);
            displaymessage(&working);
            break;

        case 5:
            if (!isValidKey(subKey)) {
                printf("Invalid substitution key\n");
                break;
            }
            encryptSubstitution(&working, subKey);
            displaymessage(&working);
            break;

        case 6:
            getreversekey(subKey, reverseKey);
            decryptSubstitution(&working, reverseKey);
            displaymessage(&working);
            break;

        case 7:
            reverseMessage(&working);
            displaymessage(&working);
            break;

        case 8:
            removeSpaces(&working);
            displaymessage(&working);
            break;

        case 9:
            frequencyAnalysis(&working);
            break;

        case 10:
            printf("Index of Coincidence: %.6f\n",
                   coincidenceIndex(working));
            break;

        case 11:
            working = original;
            printf("Message reset.\n");
            break;

        case 0:
            return 0;

        default:
            printf("Invalid choice.\n");
        }
    }

    return 0;
}