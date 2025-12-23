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
      
      for(int i = 1 ; i <= *n ; i++){
            printf("Enter user %d name : ",i);scanf("%s",users[i].name );
            printf("Enter user %d password : ",i);scanf("%s",users[i].password);
            printf("enter user %d role [0] user , [1] admin :",i);scanf("%i",&users[i].role);
            printf("Enter user %d state [0] active [1] blocked :",i);scanf("%i",&users[i].state);
      }
}
void displayUsers(struct User users[], int n){
      for (int i = 1 ; i <= n  ; i++ ){
            printf("=============================================================\n");
            printf("user %i name : %s \n", i , users[i].name);
            printf("user %i password : %s \n", i , users[i].password);
            if (users[i].role == 1 ){
                  printf("user %i role : admin\n",i);
            }
            else{
                  printf("user %i role : user\n",i);
            }
            if (users[i].role == 1 ){
                  printf("user %i state : blocked\n",i);
            }
            else{
                  printf("user %i state : active\n",i);
            }
            
      }

}
void addUser(struct User users[], int *n){
      *n = *n +1 ;
      printf("Enter user %d name : ",*n);scanf("%s",users[*n].name );
      printf("Enter user %d password : ",*n);scanf("%s",users[*n].password);
      printf("enter user %d role [0] user , [1] admin :",*n);scanf("%i",&users[*n].role);
      printf("Enter user %d state [0] active [1] blocked :",*n);scanf("%i",&users[*n].state);


}