#ifndef AUDITSECANALYSIS_H
#define AUDITSECANALYSIS_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "UserManagement.h"
// AuditSecAnalysis : 

int countUppercase(char text[]);
int countLowercase(char text[]);
int countdigits(char text[]);
float percentUppercase(char text[]);
int textLength(char text[]);
void displayTextStats(char text[]);
int veryStrongPassword(char pass[]);
void generatekey(int length , char pass[]);
bool isHexKey(char key[]);
void generateRandomPassword(int length , char pass[]);
int passwordScore(char pass[]);
float averageScore(struct User users[] , int n );
void displaySecurityReport(struct User users[], int n);
int countStrongUsers(struct User users[], int n);
void showSecurityTips();
int checkLoginFormat(char name[]);
int checkEmailFormat(char name[]);
void generateHexKey(int length , char key[]);
void top3Passwords(struct User users[], int n);
int globalSecurityLevel(struct User users[] , int n );


#endif


