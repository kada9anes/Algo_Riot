#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
// Userman  : 
struct User{
      char name[20];
      char password[20];
      int role; // 0: user, 1: admin
      int state; // 0: active, 1: blocked
};
void initUsers(struct User users[], int *n);
void displayUsers(struct User users[], int n);
void addUser(struct User users[], int *n);
int searchUser(struct User users[], int n, char name[]);
bool checkLogin(struct User users[], int n, char name[], char pass[]);
void blockUser(struct User users[], int n, char name[]);
void changeRole(struct User users[], int n, char name[],int role);
int stringLength(char str[]);
bool containsUppercase(char str[]);
bool containsSymbol(char str[]);
void saveUsers(struct User users[], int n);
#endif 