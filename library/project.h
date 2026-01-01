/*#ifndef ALGO_PROJECT_H
#define ALGO_PROJECT_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
//Encryption 
struct Message{
char text[1024];
int length;
}; 
void inputMessage(struct Message *m); 
void displaymessage(struct Message *m); // 2 written by kada
bool isLowercase(char c); //  4 written by kada
bool isUppercase(char c); 
void toUppercase(struct Message *m); //written by kada
void toLowercase(struct Message *m);
void encryptCesar(struct Message *m, int key);
void decryptCesar(struct Message *m, int key);
void removeSpaces(struct Message *m);
void getreversekey(char key[26] , char reverse[26]);
void decryptSubstitution(struct Message *m, char reverse[26]);
bool isAlphabetic(char c);
void reverseMessage(struct Message *m);
void encryptXOR(struct Message *m, int key);
void decryptXOR(struct Message *m, int key);
void encryptSubstitution(struct Message *m, char key[26]);
bool isValidKey(char key[27]);
bool compareMessages(struct Message *m1 , struct Message *m2);
int countCharacter(struct Message m, char c);
void frequencyAnalysis(struct Message *m);
float coincidenceIndex(struct Message m);

//MathSecTool
struct Matrix{
int data[10][10];
int n, p;
} ;
int isEven(int n);
int countDigits(int n);
int isPrime(int n);
int gcd(int a, int b);
int lcm(int a, int b);
long long globalmodExp(long long  base , long long exponent, long long  mod);
int factorial(int n);
int sumDigits(int n);
int reverseNumber(int n);
int isPalindromeNumber(int n);
int sumDivisors(int n);
int isPerfectNumber(int n );
int isArmstrong(int n);
int randomNumber(int min, int max);
int sumArray(int T[], int n);
float averageArray(int T[], int n);
int maxArray(int T[], int n);
int minArray(int T[], int n);
void sortAscending(int T[], int n);
void displayMatrix(struct Matrix M);
void addMatrices(struct Matrix A, struct Matrix B, struct Matrix *C);
void multiplyMatrices(struct Matrix A, struct Matrix B,struct Matrix *C);
void transposeMatrix(struct Matrix A, struct Matrix *T);
int determinant2x2(int A[2][2]);
int isSymmetric(struct Matrix M);
int isIdentity(struct Matrix M);
// LogMangement :
struct User{
      char name[128];
      char password[128];
      int role; // 0: user, 1: admin
      int state; // 0: active, 1: blocked
};

























#endif 
*/