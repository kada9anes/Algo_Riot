#include <stdio.h>
#include "../library/project.h"
#include "../library/AuditSecAnalysis.h"
#include "../library/Encryption.h"
#include "../library/LogManagement.h"
#include "../library/MathSecTool.h"
#include <math.h>
#include <string.h>
#include <stdbool.h>
void initUsers(struct User users[], int *n) {
    while (1) {
        printf("Enter number of users (max 100): ");
        if (scanf("%d", n) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        if (*n > 0 && *n <= 100) {
            break;
        }
        printf("Invalid number. Must be between 1 and 100.\n");
    }
    
    for (int i = 0; i < *n; i++) {
        printf("Enter user %d name: ", i+1);
        scanf("%19s", users[i].name);
        
        printf("Enter user %d password: ", i+1);
        scanf("%19s", users[i].password);
        simpleEncrypt(users[i].password, 13);
        
        do {
            printf("Enter user %d role [0] user, [1] admin: ", i+1);
            if (scanf("%d", &users[i].role) != 1) {
                while (getchar() != '\n');
                users[i].role = -1;
            }
        } while (users[i].role != 0 && users[i].role != 1);
        
        do {
            printf("Enter user %d state [0] active, [1] blocked: ", i+1);
            if (scanf("%d", &users[i].state) != 1) {
                while (getchar() != '\n');
                users[i].state = -1;
            }
        } while (users[i].state != 0 && users[i].state != 1);
    }
}
void displayUsers(struct User users[], int n){
      for (int i = 0 ; i < n  ; i++ ){
            printf("=============================================================\n");
            printf("user %i name : %s \n", i+1 , users[i].name);
            printf("user %i password : %s \n", i+1 , users[i].password);
            if (users[i].role == 1 ){
                  printf("user %i role : admin\n",i+1);
            }
            else{
                  printf("user %i role : user\n",i+1);
            }
            if (users[i].state == 1 ){
                  printf("user %i state : blocked\n",i+1);
            }
            else{
                  printf("user %i state : active\n",i+1);
            }
            
      }

}
void addUser(struct User users[], int *n) {
    if (*n >= 100) {
        printf("Error: Cannot add more users. Maximum limit reached.\n");
        return;
    }
    int i = *n;
    do {
      printf("Enter user %d name: ", i+1);
      scanf("%19s", users[i].name);
      if (checkLoginFormat(users[i].name) != 1)
      {
            printf("\nbad format ERROR\n");
      }
      
    }while(checkLoginFormat(users[i].name) != 1 && searchUser(users,*n, users[i].name) != -1);
    printf("Enter user %d password: ", i+1);
    scanf("%19s", users[i].password);
    simpleEncrypt(users[i].password, 13);
    do {
        printf("Enter user %d role [0] user, [1] admin: ", i+1);
        if (scanf("%d", &users[i].role) != 1) {
            while (getchar() != '\n');
            users[i].role = -1;
        }
      } while (users[i].role != 0 && users[i].role != 1);
    do {
        printf("Enter user %d state [0] active, [1] blocked: ", i+1);
        if (scanf("%d", &users[i].state) != 1) {
            while (getchar() != '\n');
            users[i].state = -1;
        }
      } while (users[i].state != 0 && users[i].state != 1);
    (*n)++;
    printf("User added successfully.\n");
}
int searchUser(struct User users[], int n, char name[]){
      for (int i = 0 ; i< n ; i++){
            if (strcmp(users[i].name,name) == 0){
                  return i ;
            }
      }
      return -1 ;
}
void deleteUser(struct User users[], int *n,char name[]) {
    int idx = searchUser(users, *n, name);
    if (idx == -1) {
        printf("User not found\n");
        return;
    }
    for (int i = idx; i < *n - 1; i++) {
        users[i] = users[i + 1];
    }
    (*n)--;
}
bool containsDigit(char str[]){
      for (int i = 0 ; str[i] != '\0' ; i++ ){
            if (str[i]>= '0' && str[i]<= '9'){
                  return true ;
            }
      }
      return false ;
}
bool containsLowercase(char str[]){
      for(int i = 0 ; str[i] != '\0' ; i++){
            if(isLowercase(str[i])){
                  return true ;
            }
      }
      return false;
}
bool containsUppercase(char str[]){
      for (int i = 0 ; str[i] != '\0' ; i++ ){
            if (isUppercase(str[i])){
                  return true ;
            }
            
      }
      return false ;
}
bool containsSymbol(char str[]){
      for (int i = 0 ; str[i] != '\0' ; i++ ){
            char c = str[i];
            if ((c >= '!' && c <= '/') ||(c >= ':' && c <= '@') ||(c >= '[' && c <= '`') ||(c >= '{' && c <= '~')) {
                  return true ;
            }
      }
      return false ;
}
bool strongPassword(char str[]){
      if (textLength(str) < 8 ){
            return false ;
      }
      if (!containsUppercase(str)){
            return false ;
      }
      if(!containsDigit(str)){
            return false ;
      }
      if (!containsSymbol(str)){
            return false ;
      }
      return true ;
}
int checkPasswordStrength(char *pass) {
    int len = strlen(pass);
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;
    if (len < 8) {
        printf("Password too short (minimum 8 characters)\n");
        return 0;
    }
    for (int i = 0; pass[i]; i++) {
        if (isUppercase(pass[i])) hasUpper = 1;
        else if (isLowercase(pass[i])) hasLower = 1;
        else if (isDigit(pass[i])) hasDigit = 1;
        else hasSpecial = 1;
    }
    if (!hasUpper) {
        printf("Password must contain at least one uppercase letter\n");
        return 0;
    }
    if (!hasLower) {
        printf("Password must contain at least one lowercase letter\n");
        return 0;
    }
    if (!hasDigit) {
        printf("Password must contain at least one digit\n");
        return 0;
    }
    if (!hasSpecial) {
        printf("Password must contain at least one special character\n");
        return 0;
    }

    return 1;
}
void ChangePassword(struct User users[], int n, char name[]) {
    int idx = searchUser(users, n, name);
    if (idx == -1) {
        printf("User not found\n");
        return;
    }
    char newpass[128];
    while (1) {
        printf("Enter new password: ");
        if (fgets(newpass, sizeof(newpass), stdin) == NULL) {
            printf("Input error\n");
            continue;
        }
        newpass[strcspn(newpass, "\n")] = '\0';
        if (strlen(newpass) == 0) {
            printf("Password cannot be empty\n");
            continue;
        }
        if (!checkPasswordStrength(newpass)) {
            printf("Weak password. Try again.\n\n");
            continue;
        }
        break;
    }
    strcpy(users[idx].password, newpass);
    printf("Password changed successfully\n");
}
int checkLogin(struct User users[], int n, char name[], char pass[]){
      for (int i = 0 ; i<n ; i++){
            if (strcmp(users[i].name,name) == 0 && strcmp(users[i].password,pass) == 0){
                  if (users[i].state == 0) return 1;
                  else return -2;
            }
            
      }
      return -1 ;
}
void blockUser(struct User users[], int n, char name[]){
      int idx = searchUser(users , n , name) ;
      if (idx != -1) users[idx].state = 1 ;
      else{
            printf("this user isn't exist");
      } 
}
void unblockUser(struct User users[], int n, char name[]){
      int idx = searchUser(users , n , name) ;
      if (idx != -1) users[idx].state = 0 ;
      else{
            printf("this user isn't exist");
      }      
}
void changeRole(struct User users[], int n, char name[],int role){
      if (role != 1 && role != 0) return; 
      int idx = searchUser(users , n , name) ;
      if (idx != -1){
      users[idx].role = role ;
      }
      else{
            printf("this user isn't exist");
      } 
      
}
void listAdmins(struct User users[], int n){
      printf("List of admins : \n");
      for (int i = 0 ; i < n ; i++ ){
            if (users[i].role == 1){
                  printf(" - %s \n" , users[i].name);
            }
      }
}
int stringLength(char str[]){
      int i = 0;
      while (str[i]!= '\0')
      {
            i++;
      }
      return i ;
      
}

void userStatistics(struct User users[] , int n){
     int admins = 0 ; int blocked = 0 ; int active = 0 ; int regular = 0 ;
      for (int i = 0 ; i < n ; i++ ){
            if(users[i].role == 1) admins++;
            else regular++;
            if(users[i].state == 1) blocked++;
            else active++;

      }
      printf("===== User Statistics =====\n");
      printf("Total users   : %d \n" , n);
      printf("Active users  : %d\n", active);
      printf("Blocked users : %d\n", blocked);
      printf("Admins        : %d\n", admins);
      printf("Regular users : %d\n", regular);
}     
void simpleEncrypt(char *text, char key) {
      for (int i = 0; text[i] != '\0'; i++) {
            if(isUppercase(text[i])) {
                  text[i] = ((text[i] - 'A' + key) % 26) + 'A';
            } else if(isLowercase(text[i])) {
                  text[i] = ((text[i] - 'a' + key) % 26) + 'a';
            }
      }
      for (int i = 0; text[i] != '\0'; i++) {
            text[i] ^= key;
      }
}

void saveUsers(struct User users[], int n){
      FILE *f = fopen("users.txt" , "w");
      if (f == NULL){
            printf("ERROR: can not open file \n");
            return;
      }
      fprintf(f,"%i\n",n);
      for (int i = 0; i < n; i++)
      {

            fprintf(f, "%s %s %d %d\n",
                users[i].name,
                users[i].password,
                users[i].role,
                users[i].state);
      }
      fclose(f);
      
}
void LoadUsers(struct User users[] , int *n){
      FILE *f = fopen("users.txt" , "r" );
      if (f == NULL){
            printf("ERROR: can not open file \n");
            return;
      }
      if (fscanf(f, "%d", n) != 1) {
        printf("Failed to read number of users\n");
        fclose(f);
        return;
      }
      for (int i = 0; i < *n; i++) {
        if (fscanf(f, "%19s %19s %d %d",
                  users[i].name,
                  users[i].password,
                  &users[i].role,
                  &users[i].state) != 4) {
            printf("Error reading user %d\n", i + 1);
            fclose(f);
            return;
        }
    }
    fclose(f);
}
