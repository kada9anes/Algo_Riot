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
      int conter = 0;
      for (int i  = 0 ; i != '\0';i++){
            if (isUppercase(text[i])){
                  conter ++ ;
            }
      }
      return conter ;
}
int countLowercase(char text[]){
      int conter = 0;
      for (int i = 0 ; i != '\0';i++){
            if (isLowercase(text[i])){
                  conter++ ;
            }
      } 
      return conter ;
}
int countDigits(char text[]){
      int conter = 0;
      for (int i  = 0 ; i != '\0';i++){
            if (isDigit(text[i])){
                  conter++ ;
            }
      }
      return conter ;
}
float percentUppercase(char text[]){
      int total = strlen(text);
      int uppercase = 0;
      if(total == 0) return 0.0f; 
      for(int i =0 ; i < total ; i++ ){
            if(isUppercase(text[i])) uppercase++;
      }
      return ((float)uppercase / total) *100.0f;
}
int textLength(char text[]){
      int conter = 0 ;
      while (text[conter]!='\0')
      {
            conter++;
      }
      return conter ;
      
}
void displayTextStats(char text[]){
      int size = strlen(text);
      int uppercase = countUppercase(text);
      int lowercase = countLowercase;
      int digits = countDigits;
      int special = size - uppercase - lowercase - digits ;
      printf("===== User Statistics =====\n");
      printf("Total characters         : %d \n" , size);
      printf("Total uppercase letters  : %d \n" , uppercase);
      printf("Total lowercase letters  : %d \n" , lowercase);
      printf("Total digits             : %d \n" , digits);
      printf("Total special characters : %d \n" , special);

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
void generatekey(int length , char pass[]){
      const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
      int charsetSize = sizeof(charset) -1 ;
      for (int i = 0 ; i < length ; i++){
            int keyIndex = rand() % charsetSize ;
            pass[i] = charset[keyIndex];
      }
      pass[length] = '\0' ;
}
bool isHexKey(char key[]){
      for (int i = 0 ; i != 0 ; i++){
            if (!isxdigit(key[i])){ // we can use if (key[i] >=0 && ...|| key[i]>='A'&& ... || ...)
                  return false ;
            }
      }
      return true ;
}
void generateRandomPassword(int length , char pass[]){
      if (length < 4) { 
        printf("Password length must be at least 4\n");
        pass[0] = '\0';
        return;
    }
    srand(time(NULL));
    const char uppercase[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char lowercase[] = "abcdefghijklmnopqrstuvwxyz";
    const char digits[]    = "0123456789";
    const char symbols[]   = "!@#$%^&*()-_=+[]{}|;:,.<>?/";
    int i =0;
    pass[i++] = uppercase[rand() % strlen(uppercase)];
    pass[i++] = lowercase[rand() % strlen(lowercase)];
    pass[i++] = digits[rand() % strlen(digits)];
    pass[i++] = symbols[rand() % strlen(symbols)];
    const char allchar[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()-_=+[]{}|;:,.<>?/";
    int size = strlen(allchar);
    for(; i< length ; i++){
      pass[i] = allchar[rand() % size ]; 
    }
    pass[length] = '\0';
    for(int i = 0 ; i < length ; i++){
      int j = rand() % length ;
      char tmp = pass[i];
      pass[i] = pass[j];
      pass[j] = tmp ;
    }
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
float averageScore(struct User users[] , int n ){
      if (n == 0) return 0.0f;
      int  total = 0;
      for (int i = 0 ; i < n ; i++){
          total += passwordScore(users[i].password);
      }
      return (float)total / n;
}
void displaySecurityReport(struct User users[], int n) {
    if (n == 0) {
        printf("No users to display.\n");
        return;
      }
    int numUsersActive = 0;
    int numUsersAdmin = 0;
    int numUsersStrongPass = 0;
    for (int i = 0; i < n; i++) {
        if (users[i].state == 0) numUsersActive++;
        if (users[i].role == 1) numUsersAdmin++;
        if (veryStrongPassword(users[i].password)) numUsersStrongPass++;
    }
    float avgScore = averageScore(users, n);
    printf("===== User Security Report =====\n");
    printf("Total users               : %d\n", n);
    printf("Active users              : %d\n", numUsersActive);
    printf("Blocked users             : %d\n", n - numUsersActive);
    printf("Admin users               : %d\n", numUsersAdmin);
    printf("Regular users             : %d\n", n - numUsersAdmin);
    printf("Users with strong password: %d\n", numUsersStrongPass);
    printf("Users needing password update:\n");

    for (int i = 0; i < n; i++) {
        if (!veryStrongPassword(users[i].password)) {
            printf(" - %s (Score: %d)\n", users[i].name, passwordScore(users[i].password));
        }
    }
    printf("Average password score: %.2f\n", avgScore);
    printf("================================\n");
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
      if (name[0] == '\0') return false;
      if(!(isAlphabetic(name[0]))) return false;
      for (int i = 0 ; name[i] != '\0' ; i++){
            char c = name[i];
            if(!(isAlphabetic(c) || isdigit(c) || c =='_')){
                  return false;
            }
      }
      return true ;
}
// this function needed for eamil checking :
      bool oneAt(char name[]){
            int conter = 0;
            for (int i = 0; name[i] != '\0'; i++){
                  if (name[i] == '@')
                        conter++;
            }
            return conter == 1 ;
      }
      bool LocalPart(char name[]){
            if (name[0] == '.' || name[0] == '@')
                  return false;

            for (int i = 0; name[i] != '@'; i++){
                  if (name[i] == '\0')
                        return false;

                  if (!((name[i] >= 'a' && name[i] <= 'z') ||(name[i] >= 'A' && name[i] <= 'Z') ||name[i] == '.' || name[i] == '_')) return false;

                  if (name[i] == '.' && name[i+1] == '.')
                        return false;
            }
      return true;
      }    
      bool DomainPart (char name[]){
            int idxAt = -1 ;
            int conterDots = 0;
            for (int i = 0; name[i] != '\0'; i++)
            {
                  if (name[i]== '@') idxAt = i ;
            }
            if (idxAt == -1) return false;
            if (name[idxAt+1]=='\0'||name[idxAt+1]=='.') return false ;
            for (int  j=idxAt+1 ; name[j] !='\0'; j++)
            {
                  if (!((name[j]>='a'&& name[j]<='z')||(name[j]>='A'&& name[j]<='Z')||name[j]== '.')||((name[j]=='.')&&(name[j+1]=='.')))
                  {
                        return false ;
                  }
                  if (name[j]=='.')
                  {
                        conterDots++;
                  }
                  
                  
            }
            if (conterDots == 0 )
            {
                  return false ;
            }
            if (name[strlen(name)-1]== '.')return false ;

            return true ;
            
            
      }
bool checkEmailFormat(char name[]){
      return (oneAt(name)&& LocalPart(name)&& DomainPart(name))
}

      


void generateHexKey(int length , char key[]){ //need to seed random
      if(length <= 0){
            key[0] = '\0';
            return;
      }
      const char HEX[]="0123456789ABCDEF";
      for(int i = 0 ; i < length ; i++){
            key[i] = HEX[rand() % 16]; 
      }
      key[length] = '\0';
}
void top3Passwords(struct User users[], int n){// problem of users less than 3 users 
      int top [3]={-1,-1,-1};
      int j= 0 ;
      int k = 7 ;
      while (j < 3 && k > 0)
      {
            for (int i = 0; i < n; i++)
            {
                  if (passwordScore(users[i].password)==k && j < 3)
                  {
                        top[j]=i;
                        j++;
                  }
                  
            }
            k--;
      }
    for (int i = 0; i < 3; i++) {
        if (top[i] != -1)
            printf("Top %d strong password: %s\n", i+1, users[top[i]].password);
        else
            printf("Top %d strong password: N/A\n", i+1);
    }
}
int globalSecurityLevel(struct User users[] , int n ){
      float avr = averageScore(users,n);
      if (avr>= 6){
            return 3 ; // level 3 strong 
      }
      else if (avr<6 && avr >=3){
            return 2 ; // level 2 mid 
      }
      else if (avr>= 1 && avr <3){
            return 1 ; // level 3 weak 
      }
      else return 0 ; // no sec
}
// all this not test 100% there exist errors dont touch it 
