#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "library/project.h"

// ==================== UTILITY FUNCTIONS ====================

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pauseScreen() {
    printf("\nPress ENTER to continue...");
    clearInputBuffer();
}

void printSeparator() {
    printf("\n========================================\n");
}

// ==================== LIBRARY 1: MATH & ARRAYS ====================

void testMathFunctions() {
    int choice, n, a, b, base, exp, mod;
    
    while (1) {
        printSeparator();
        printf("=== MATH FUNCTIONS MENU ===\n");
        printf("1.  isEven\n");
        printf("2.  countDigits\n");
        printf("3.  isPrime\n");
        printf("4.  gcd & lcm\n");
        printf("5.  modExp\n");
        printf("6.  factorial\n");
        printf("7.  sumDigits\n");
        printf("8.  reverseNumber\n");
        printf("9.  isPalindrome\n");
        printf("10. sumDivisors\n");
        printf("11. isPerfectNumber\n");
        printf("12. isArmstrong\n");
        printf("13. randomNumber\n");
        printf("0.  Back\n");
        printf("Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        
        switch (choice) {
        case 1:
            printf("Enter number: ");
            scanf("%d", &n);
            clearInputBuffer();
            printf("Result: %s\n", isEven(n) == 1 ? "EVEN" : "ODD");
            pauseScreen();
            break;
            
        case 2:
            printf("Enter number: ");
            scanf("%d", &n);
            clearInputBuffer();
            printf("Number of digits: %d\n", countDigits(n));
            pauseScreen();
            break;
            
        case 3:
            printf("Enter number: ");
            scanf("%d", &n);
            clearInputBuffer();
            printf("Result: %s\n", isPrime(n) == 1 ? "PRIME" : "NOT PRIME");
            pauseScreen();
            break;
            
        case 4:
            printf("Enter two numbers (a b): ");
            scanf("%d %d", &a, &b);
            clearInputBuffer();
            printf("GCD(%d, %d) = %d\n", a, b, gcd(a, b));
            printf("LCM(%d, %d) = %d\n", a, b, lcm(a, b));
            pauseScreen();
            break;
            
        case 5:
            printf("Enter base exponent modulo: ");
            scanf("%d %d %d", &base, &exp, &mod);
            clearInputBuffer();
            printf("%d^%d mod %d = %d\n", base, exp, mod, modExp(base, exp, mod));
            pauseScreen();
            break;
            
        case 6:
            printf("Enter number: ");
            scanf("%d", &n);
            clearInputBuffer();
            int fact = factorial(n);
            if (fact == -1) {
                printf("Factorial not defined for negative numbers\n");
            } else {
                printf("%d! = %d\n", n, fact);
            }
            pauseScreen();
            break;
            
        case 7:
            printf("Enter number: ");
            scanf("%d", &n);
            clearInputBuffer();
            printf("Sum of digits: %d\n", sumDigits(n));
            pauseScreen();
            break;
            
        case 8:
            printf("Enter number: ");
            scanf("%d", &n);
            clearInputBuffer();
            printf("Reversed: %d\n", reverseNumber(n));
            pauseScreen();
            break;
            
        case 9:
            printf("Enter number: ");
            scanf("%d", &n);
            clearInputBuffer();
            printf("Result: %s\n", isPalindrome(n) == 1 ? "PALINDROME" : "NOT PALINDROME");
            pauseScreen();
            break;
            
        case 10:
            printf("Enter number: ");
            scanf("%d", &n);
            clearInputBuffer();
            int sum = sumDivisors(n);
            if (sum == -1) {
                printf("Not defined for non-positive numbers\n");
            } else {
                printf("Sum of divisors: %d\n", sum);
            }
            pauseScreen();
            break;
            
        case 11:
            printf("Enter number: ");
            scanf("%d", &n);
            clearInputBuffer();
            printf("Result: %s\n", isPerfectNumber(n) == 1 ? "PERFECT" : "NOT PERFECT");
            pauseScreen();
            break;
            
        case 12:
            printf("Enter number: ");
            scanf("%d", &n);
            clearInputBuffer();
            printf("Result: %s\n", isArmstrong(n) == 1 ? "ARMSTRONG" : "NOT ARMSTRONG");
            pauseScreen();
            break;
            
        case 13:
            printf("Enter min max: ");
            scanf("%d %d", &a, &b);
            clearInputBuffer();
            printf("Random number: %d\n", randomNumber(a, b));
            pauseScreen();
            break;
            
        case 0:
            return;
            
        default:
            printf("Invalid choice!\n");
            pauseScreen();
        }
    }
}

void testArrayFunctions() {
    int choice, n, i;
    int arr[100];
    
    while (1) {
        printSeparator();
        printf("=== ARRAY FUNCTIONS MENU ===\n");
        printf("1. sumArray\n");
        printf("2. averageArray\n");
        printf("3. maxArray\n");
        printf("4. minArray\n");
        printf("5. sortAscending\n");
        printf("0. Back\n");
        printf("Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        
        if (choice == 0) return;
        
        printf("Enter array size: ");
        scanf("%d", &n);
        clearInputBuffer();
        
        printf("Enter %d elements: ", n);
        for (i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        clearInputBuffer();
        
        switch (choice) {
        case 1:
            printf("Sum: %d\n", sumArray(arr, n));
            pauseScreen();
            break;
            
        case 2:
            printf("Average: %.2f\n", averageArray(arr, n));
            pauseScreen();
            break;
            
        case 3:
            printf("Max: %d\n", maxArray(arr, n));
            pauseScreen();
            break;
            
        case 4:
            printf("Min: %d\n", minArray(arr, n));
            pauseScreen();
            break;
            
        case 5:
            sortAscending(arr, n);
            printf("Sorted array: ");
            for (i = 0; i < n; i++) {
                printf("%d ", arr[i]);
            }
            printf("\n");
            pauseScreen();
            break;
            
        default:
            printf("Invalid choice!\n");
            pauseScreen();
        }
    }
}

void testMatrixFunctions() {
    int choice;
    struct Matrix A, B, C;
    
    while (1) {
        printSeparator();
        printf("=== MATRIX FUNCTIONS MENU ===\n");
        printf("1. Display Matrix\n");
        printf("2. Add Matrices\n");
        printf("3. Multiply Matrices\n");
        printf("4. Transpose Matrix\n");
        printf("5. Determinant 2x2\n");
        printf("6. Check Symmetric\n");
        printf("7. Check Identity\n");
        printf("0. Back\n");
        printf("Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        
        switch (choice) {
        case 1:
            printf("Enter matrix dimensions (rows cols): ");
            scanf("%d %d", &A.n, &A.p);
            clearInputBuffer();
            printf("Enter matrix elements:\n");
            for (int i = 0; i < A.n; i++) {
                for (int j = 0; j < A.p; j++) {
                    scanf("%d", &A.data[i][j]);
                }
            }
            clearInputBuffer();
            printf("\nMatrix:\n");
            displayMatrix(A);
            pauseScreen();
            break;
            
        case 2:
            printf("Enter Matrix A dimensions (rows cols): ");
            scanf("%d %d", &A.n, &A.p);
            clearInputBuffer();
            printf("Enter Matrix A elements:\n");
            for (int i = 0; i < A.n; i++) {
                for (int j = 0; j < A.p; j++) {
                    scanf("%d", &A.data[i][j]);
                }
            }
            clearInputBuffer();
            
            printf("Enter Matrix B dimensions (rows cols): ");
            scanf("%d %d", &B.n, &B.p);
            clearInputBuffer();
            printf("Enter Matrix B elements:\n");
            for (int i = 0; i < B.n; i++) {
                for (int j = 0; j < B.p; j++) {
                    scanf("%d", &B.data[i][j]);
                }
            }
            clearInputBuffer();
            
            addMatrices(A, B, &C);
            printf("\nResult (A + B):\n");
            displayMatrix(C);
            pauseScreen();
            break;
            
        case 3:
            printf("Enter Matrix A dimensions (rows cols): ");
            scanf("%d %d", &A.n, &A.p);
            clearInputBuffer();
            printf("Enter Matrix A elements:\n");
            for (int i = 0; i < A.n; i++) {
                for (int j = 0; j < A.p; j++) {
                    scanf("%d", &A.data[i][j]);
                }
            }
            clearInputBuffer();
            
            printf("Enter Matrix B dimensions (rows cols): ");
            scanf("%d %d", &B.n, &B.p);
            clearInputBuffer();
            printf("Enter Matrix B elements:\n");
            for (int i = 0; i < B.n; i++) {
                for (int j = 0; j < B.p; j++) {
                    scanf("%d", &B.data[i][j]);
                }
            }
            clearInputBuffer();
            
            multiplyMatrices(A, B, &C);
            printf("\nResult (A * B):\n");
            displayMatrix(C);
            pauseScreen();
            break;
            
        case 4:
            printf("Enter matrix dimensions (rows cols): ");
            scanf("%d %d", &A.n, &A.p);
            clearInputBuffer();
            printf("Enter matrix elements:\n");
            for (int i = 0; i < A.n; i++) {
                for (int j = 0; j < A.p; j++) {
                    scanf("%d", &A.data[i][j]);
                }
            }
            clearInputBuffer();
            
            transposeMatrix(A, &C);
            printf("\nTranspose:\n");
            displayMatrix(C);
            pauseScreen();
            break;
            
        case 5: {
            int mat[2][2];
            printf("Enter 2x2 matrix elements:\n");
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    scanf("%d", &mat[i][j]);
                }
            }
            clearInputBuffer();
            printf("Determinant: %d\n", determinant2x2(mat));
            pauseScreen();
            break;
        }
            
        case 6:
            printf("Enter square matrix dimension: ");
            scanf("%d", &A.n);
            A.p = A.n;
            clearInputBuffer();
            printf("Enter matrix elements:\n");
            for (int i = 0; i < A.n; i++) {
                for (int j = 0; j < A.p; j++) {
                    scanf("%d", &A.data[i][j]);
                }
            }
            clearInputBuffer();
            printf("Result: %s\n", isSymmetric(A) == 1 ? "SYMMETRIC" : "NOT SYMMETRIC");
            pauseScreen();
            break;
            
        case 7:
            printf("Enter square matrix dimension: ");
            scanf("%d", &A.n);
            A.p = A.n;
            clearInputBuffer();
            printf("Enter matrix elements:\n");
            for (int i = 0; i < A.n; i++) {
                for (int j = 0; j < A.p; j++) {
                    scanf("%d", &A.data[i][j]);
                }
            }
            clearInputBuffer();
            printf("Result: %s\n", isIdentity(A) == 1 ? "IDENTITY" : "NOT IDENTITY");
            pauseScreen();
            break;
            
        case 0:
            return;
            
        default:
            printf("Invalid choice!\n");
            pauseScreen();
        }
    }
}

// ==================== LIBRARY 2: MESSAGE PROCESSING ====================

void testMessageFunctions() {
    struct Message original;
    struct Message working;
    char subKey[27] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    char reverseKey[26];
    int choice, key;

    printf("\n=== MESSAGE INPUT ===\n");
    inputMessage(&original);
    working = original;

    while (1) {
        printSeparator();
        printf("=== MESSAGE OPERATIONS MENU ===\n");
        printf("1.  Display message\n");
        printf("2.  toUppercase\n");
        printf("3.  toLowercase\n");
        printf("4.  Remove spaces\n");
        printf("5.  Reverse message\n");
        printf("6.  Caesar encrypt\n");
        printf("7.  Caesar decrypt\n");
        printf("8.  XOR encrypt/decrypt\n");
        printf("9.  Substitution encrypt\n");
        printf("10. Substitution decrypt\n");
        printf("11. Frequency analysis\n");
        printf("12. Index of Coincidence\n");
        printf("13. Count character\n");
        printf("14. Compare with another message\n");
        printf("15. Reset message\n");
        printf("16. Input new message\n");
        printf("0.  Back\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
        case 1:
            printf("Current message: ");
            displaymessage(&working);
            pauseScreen();
            break;

        case 2:
            toUppercase(&working);
            printf("Result: ");
            displaymessage(&working);
            pauseScreen();
            break;

        case 3:
            toLowercase(&working);
            printf("Result: ");
            displaymessage(&working);
            pauseScreen();
            break;

        case 4:
            removeSpaces(&working);
            printf("Result: ");
            displaymessage(&working);
            pauseScreen();
            break;

        case 5:
            reverseMessage(&working);
            printf("Result: ");
            displaymessage(&working);
            pauseScreen();
            break;

        case 6:
            printf("Enter Caesar key: ");
            scanf("%d", &key);
            clearInputBuffer();
            encryptCesar(&working, key);
            printf("Encrypted: ");
            displaymessage(&working);
            pauseScreen();
            break;

        case 7:
            printf("Enter Caesar key: ");
            scanf("%d", &key);
            clearInputBuffer();
            decryptCesar(&working, key);
            printf("Decrypted: ");
            displaymessage(&working);
            pauseScreen();
            break;

        case 8:
            printf("Enter XOR key (0-255): ");
            scanf("%d", &key);
            clearInputBuffer();
            encryptXOR(&working, key);
            printf("Result: ");
            displaymessage(&working);
            pauseScreen();
            break;

        case 9:
            if (!isValidKey(subKey)) {
                printf("Invalid substitution key!\n");
            } else {
                encryptSubstitution(&working, subKey);
                printf("Encrypted: ");
                displaymessage(&working);
            }
            pauseScreen();
            break;

        case 10:
            getreversekey(subKey, reverseKey);
            decryptSubstitution(&working, reverseKey);
            printf("Decrypted: ");
            displaymessage(&working);
            pauseScreen();
            break;

        case 11:
            printf("\nFrequency Analysis:\n");
            frequencyAnalysis(&working);
            pauseScreen();
            break;

        case 12:
            printf("Index of Coincidence: %.6f\n", coincidenceIndex(working));
            pauseScreen();
            break;

        case 13: {
            char c;
            printf("Enter character to count: ");
            scanf(" %c", &c);
            clearInputBuffer();
            printf("Count of '%c': %d\n", c, countCharacter(working, c));
            pauseScreen();
            break;
        }

        case 14: {
            struct Message other;
            printf("Enter message to compare: ");
            inputMessage(&other);
            printf("Result: %s\n", compareMessages(&working, &other) ? "EQUAL" : "NOT EQUAL");
            pauseScreen();
            break;
        }

        case 15:
            working = original;
            printf("Message reset to original.\n");
            pauseScreen();
            break;

        case 16:
            printf("Enter new message: ");
            inputMessage(&original);
            working = original;
            printf("New message set.\n");
            pauseScreen();
            break;

        case 0:
            return;

        default:
            printf("Invalid choice!\n");
            pauseScreen();
        }
    }
}

// ==================== MAIN MENU ====================

int main(void) {
    int choice;
    
    // Seed random number generator ONCE
    srand(time(NULL));
    
    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║    COMPREHENSIVE LIBRARY TEST SUITE   ║\n");
    printf("║         Two Libraries in One          ║\n");
    printf("╚════════════════════════════════════════╝\n");

    while (1) {
        printSeparator();
        printf("=== MAIN MENU ===\n");
        printf("1. Math Functions (Library 1)\n");
        printf("2. Array Functions (Library 1)\n");
        printf("3. Matrix Functions (Library 1)\n");
        printf("4. Message Processing (Library 2)\n");
        printf("0. Exit\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
        case 1:
            testMathFunctions();
            break;

        case 2:
            testArrayFunctions();
            break;

        case 3:
            testMatrixFunctions();
            break;

        case 4:
            testMessageFunctions();
            break;

        case 0:
            printf("\nExiting program. Goodbye!\n");
            return 0;

        default:
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}