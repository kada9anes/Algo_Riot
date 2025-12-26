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
      int inx = searchUser(users , n , name) ;
      if (inx != -1) users[inx].state = 1 ;
      else{
            printf("this user isn't exist");
      } 
      
}