#include <stdio.h>
#include "../library/project.h"
#include "../library/AuditSecAnalysis.h"
#include "../library/Encryption.h"
#include "../library/LogManagement.h"
#include "../library/MathSecTool.h"
#include <math.h>
#include <string.h>
#include <stdbool.h>
void initUsers(struct User users[], int *n){
      do
      {
            printf("Ener the number of user that you wont to start : ");
            scanf("%d",n);
      } while (*n <= 0);
      
      for(int i = 0 ; i < *n ; i++){
            printf("Enter user %d name : ",i+1);scanf("%19s",users[i].name );
            printf("Enter user %d password : ",i+1);scanf("%19s",users[i].password);
            do {
                  printf("enter user %d role [0] user , [1] admin :",i+1);scanf("%i",&users[i].role);
            }while(users[i].role != 1 && users[i].role != 0);
            do{
                  printf("Enter user %d state [0] active [1] blocked :",i+1);scanf("%i",&users[i].state);
            }while(users[i].state != 1 && users[i].state != 0);
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
void addUser(struct User users[], int *n){
      int i = *n;
      (*n)++ ;
      printf("Enter user %d name : ",i+1);scanf("%19s",users[i].name );
      printf("Enter user %d password : ",i+1);scanf("%19s",users[i].password);
      do{
      printf("enter user %d role [0] user , [1] admin :",i+1);scanf("%i",&users[i].role);
      }while(users[i].role != 1 && users[i].role != 0);
      do{
      printf("Enter user %d state [0] active [1] blocked :",i+1);scanf("%i",&users[i].state);
      }while(users[i].state != 1 && users[i].state != 0);


}
void deleteUser(struct User users[], int *n, const char name[]) {
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
int searchUser(struct User users[], int n, char name[]){
      for (int i = 0 ; i< n ; i++){
            if (strcmp(users[i].name,name) == 0){
                  return i ;
            }
      }
      return -1 ;
}
void ChangePassword(struct User users[] , int n , char name[]){
      int idx = searchUser(users , n , name);
      if(idx != -1){
            char newpass[128];
            int len = 0 ;
            printf("what is the new password : ");
            if(fgets(newpass , sizeof(newpass), stdin) != NULL){
                   len = strlen(newpass);
                  if(len > 0 && newpass[len -1] == '\n'){
                        newpass[len -1] = '\0';
                  }
            }
            if (len <= 1) {
                  printf("Password cannot be empty\n");
                  return;
            }
            if (!strongPassword(newpass)) {
                  printf("Weak password\n");
                   return;
          }
            strcpy(users[idx].password , newpass);
            printf("password changed successfully \n");
      }else{
            printf("User not found \n");
      }
}
bool checkLogin(struct User users[], int n, char name[], char pass[]){
      for (int i = 0 ; i<n ; i++){
            if (strcmp(users[i].name,name) == 0 && strcmp(users[i].password,pass) == 0 && users[i].state == 0){
                  return true ;
            }
      }
      return false ;
}
bool strongPassword(char str[]){
      if (stringLength(str) < 8 ){
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
void userStatistics(struct User users[] , int n){
     int admins = 0 ; int blocked = 0 ; int active = 0 ; int regular = 0 ;
      for (int i = 0 ; i < *n ; i++ ){
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
        if (fscanf(f, "%127s %127s %d %d",
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
