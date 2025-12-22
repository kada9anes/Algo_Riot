#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "library/project.h"

int main() {
    struct Message msg;
    
    // 1. Input message
    inputMessage(&msg);
    printf("Original message: ");
    displaymessage(&msg);

    // 2. Convert to uppercase
    toUppercase(&msg);
    printf("Uppercase: ");
    displaymessage(&msg);

    // 3. Convert to lowercase
    toLowercase(&msg);
    printf("Lowercase: ");
    displaymessage(&msg);

    // 4. Reverse message
    reverseMessage(&msg);
    printf("Reversed: ");
    displaymessage(&msg);

    // 5. Caesar encryption
    encryptCesar(&msg, 3); // key = 3
    printf("Caesar encrypted (+3): ");
    displaymessage(&msg);

    // 6. XOR encryption
    encryptXOR(&msg, 42); // key = 42
    printf("XOR encrypted (42): ");
    displaymessage(&msg);

    // 7. Substitution encryption
    char subKey[26] = "QWERTYUIOPASDFGHJKLZXCVBNM"; // valid key
    if (!isValidKey(subKey)) {
        printf("Substitution key is invalid.\n");
    } else {
        encryptSubstitution(&msg, subKey);
        printf("Substitution encrypted: ");
        displaymessage(&msg);
    }

    // 8. Count characters
    char testChar = 'A';
    int count = countCharacter(msg, testChar);
    printf("Number of '%c' in message: %d\n", testChar, count);

    // 9. Coincidence index
    float ic = coincidenceIndex(msg);
    printf("Index of Coincidence: %f\n", ic);

    return 0;
}

      