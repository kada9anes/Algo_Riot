#include <stdio.h>
#include "../library/project.h"
#include "../library/AuditSecAnalysis.h"
#include "../library/Encryption.h"
#include "../library/LogManagement.h"
#include "../library/MathSecTool.h"
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "AuditSecAnalysis.h"
int countUppercase(char text[])
{
      int cont = 0;
      for (int i  = 0 ; i != '\0';i++){
            if (text[i]>='A'&& text<='Z'){
                  cont ++ ;
            }
      }
      return cont ;
}
int countDigits(char text[]){
      int cont = 0;
      for (int i  = 0 ; i != '\0';i++){
            if (text[i]>='0'&& text<='9'){
                  cont ++ ;
            }
      }
      return cont ;
}
int textLength(char text[]){
      cont = 0 ;
      while (text[i]!='\0')
      {
            cont ++;
      }
      return cont ;
      
}
bool veryStrongPassword(char pass[]){
      bool hasUpper = false ;
      bool hasLower = false ;
      bool hasSymbol = false ; 
      for (int i = 0; str[i] != '\0'; i++) {

            if (pass[i] >= 'A' && pass[i] <= 'Z') {
                  hasUpper = true;
            }
            else if (pass[i] >= 'a' && pass[i] <= 'z') {
                  hasLower = true;
            }
            else if ((pass[i] >= 33 && pass[i] <= 47) ||(pass[i] >= 58 && pass[i] <= 64) ||(pass[i] >= 91 && pass[i] <= 96) ||(pass[i] >= 123 && pass[i] <= 126)) {
                  hasSymbol = true;
            }
      }
      if (hasLower && hasUpper && hasSymbol && textLength(pass)>= 12){
            return true ;
      else{
            return false ;
      }
      }
}
bool isHexKey(char key[]){
      for (int i = 0 ; i != 0 ; i++){
            if (!isxdigit(key[i])){ // we can use if (key[i] >=0 && ...|| key[i]>='A'&& ... || ...)
                  return false ;
            }
      }
      return true ;
}
int passwordScore(char pass[]){
      bool hasUpper = false ;
      bool hasLower = false ;
      bool hasSymbol = false ; 
      bool longer= textLength(pass)>= 12 ;
      for (int i = 0; pass[i] != '\0'; i++) {

            if (pass[i] >= 'A' && pass[i] <= 'Z') {
                  hasUpper = true;
            }
            else if (pass[i] >= 'a' && pass[i] <= 'z') {
                  hasLower = true;
            }
            else if ((pass[i] >= 33 && pass[i] <= 47) ||(pass[i] >= 58 && pass[i] <= 64) ||(pass[i] >= 91 && pass[i] <= 96) ||(pass[i] >= 123 && pass[i] <= 126)) {
                  hasSymbol = true;
            }
      }
      return hasLower + hasSymbol*2 + longer*3 + hasUpper ;
}
void displaySecurityReport(struct User users[], int n){
      int numUsersAdmin = 0 ;
      int numUsersActive = 0 ; 
      int numUsersStrongPass = 0 ;
      printf("the number of users is : %d",n);
      for (int i = 0 ; i < n ; i ++){
            if (users[i].state == 0){
                  numUsersActive++;
            }
            else if (users[i].role == 1){
                  numUsersAdmin++;
            }
            else if (veryStrongPassword(users[i].password)){
                  numUsersStrongPass++
            } 
      }
      printf("the number of user active is : %i and blocked users is : %i\n"numUsersActive,n-numUsersActive);
      printf("the number of user admin is : %i and normal users is : %i\n"numUsersAdmin,n-numUsersAdmin);
      printf("the number of user hase strong password is : %i and blocked users is : %i\n"numUsersStrongPass,n-numUsersStrongPass);
      printf("users that need to change passwords : \n");
      for (int i = 0; i < n; i++)
      {
            if (!veryStrongPassword(users[i].password))
            {
                  printf("%s\n",users[i].name);
                  printf("the password strong score is : %i",passwordScore(users[i].password));
            }
            
      }
      


}
void showSecurityTips(){
    printf("General Password Security Advice:\n");
    printf("- Use at least 8–12 characters\n");
    printf("- Include uppercase, lowercase, numbers, and symbols\n");
    printf("- Avoid common words, names, and dates\n");
    printf("- Do not reuse passwords across services\n");
    printf("- Avoid patterns like 123456 or qwerty\n");
    printf("- Change passwords after any suspected breach\n");
    printf("- Use a password manager if possible\n");
    printf("- Enable two-factor authentication (2FA)\n");
}
bool checkLoginFormat(char name[]){
      bool empty = false ;
      bool includespaces = false ;
      bool includesymbols = false ;
      bool startdijit = false ; 
      for (int i = 0 ; i <strlen(name) ;i++){
            if (name != '\0') empty true ; 
            else if (name[i]== ' ') includespaces = true ;
            else if ((name[i] >= 33 && name[i] <= 47) ||(name[i] >= 58 && name[i] <= 64) ||(name[i] >= 91 && name[i] <= 96) ||(name[i] >= 123 && name[i] <= 126)) includesymbols = true ;
            else if (name[0]>=0 && name[0]<= 9) startdijit = true;
      }
      if (empty && !includespaces && !includesymbols && !startdijit) return true;
      else return true ;
}
void top3Passwords(struct User users[], int n){// problem of users less than 3 users 
      int top [3]={-1,-1,-1};
      int j= 0 ;
      int k = 7 ;
      while ((top[0]==-1 ||top[1]==-1 ||top[2]==-1)&& k >0)
      {
            for (int i = 0; i < n; i++)
            {
                  if (passwordScore(users[i].password)==k)
                  {
                        top[j]=i;
                        j++;
                        if (j==3) break;
                  }
                  
            }
            k--;
            if (j==3)
            {
                  break;
            }
            
            
      }
      printf("the 1st strong password is : %s",users[top[0]].password);
      printf("the 2nd strong password is : %s",users[top[1]].password);
      printf("the 3rd strong password is : %s",users[top[2]].password);
}

