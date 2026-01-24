#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

struct Message{
char text[1024];
int length;
}; 
void inputMessage(struct Message *m); 
void displaymessage(struct Message *m); // 2 written by kada
bool isLowercase(char c); //  4 written by kada
bool isUppercase(char c); 
bool isDigit(char c);
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
int randomPrime(int min, int max);
#endif 