#include <stdio.h>
#include "../library/project.h"
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
            printf("Enter user %d name : ",i+1);scanf("%100s",users[i].name );
            printf("Enter user %d password : ",i+1);scanf("%100s",users[i].password);
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
      printf("Enter user %d name : ",i+1);scanf("%100s",users[i].name );
      printf("Enter user %d password : ",i+1);scanf("%100s",users[i].password);
      do{
      printf("enter user %d role [0] user , [1] admin :",i+1);scanf("%i",&users[i].role);
      }while(users[i].role != 1 && users[i].role != 0);
      do{
      printf("Enter user %d state [0] active [1] blocked :",i+1);scanf("%i",&users[i].state);
      }while(users[i].state != 1 && users[i].state != 0);


}
int searchUser(struct User users[], int n, char name[]){
      for (int i = 0 ; i< n ; i++){
            if (strcmp(users[i].name,name) == 0){
                  return i ;
            }
      }
      return -1 ;
}
bool checkLogin(struct User users[], int n, char name[], char pass[]){
      for (int i = 0 ; i<n ; i++){
            if (strcmp(users[i].name,name) == 0 && strcmp(users[i].password,pass) == 0 && users[i].state == 0){
                  return true ;
            }
      }
      return false ;
}
void blockUser(struct User users[], int n, char name[]){
      int idx = searchUser(users , n , name) ;
      if (idx != -1) users[idx].state = 1 ;
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
int stringLength(char str[]){
      int i = 0;
      while (str[i]!= '\0')
      {
            i++;
      }
      return i ;
      
}
bool containsUppercase(char str[]){
      for (int i = 0 ; i < stringLength(str) ; i++ ){
            if (str[i]>= 'A'&& str[i]<= 'Z'){
                  return true ;
            }
            
      }
      return false ;
}
bool containsSymbol(char str[]){
      for (int i = 0 ; i < stringLength(str) ; i++ ){
            if ((str[i]>= 33 && str[i]<=47)||(str[i]>= 58 && str[i]<=64)||(str[i]>= 91 && str[i]<=96)||(str[i]>= 123 && str[i]<=126)){
                  return true ;
            }
            
      }
      return false ;
}void saveUsers(struct User users[], int n){
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
