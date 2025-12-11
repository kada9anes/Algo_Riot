#include <stdio.h>
#include "../library/project.h"
#include <math.h>
void inputMessage(struct Message m[]){
      printf("Enter the length of your massage ;)");scanf("%i",&m->length);
      printf("Enter the message ;)");scanf("%s",&m->text );
}
// for you 
int isUppercase(char c){
      if ( c <= 90 && c >=65 ){
            return 1 ;
      }
      else{
            return 0 ; // brghot sad that we chould use 1 and 0 best then 0 and -1  
      }
}
// for you
int isAlphabetic(char c){
      if ( (c <= 90 && c >=65) || (c <= 122 && c>= 97) ){
            return 1 ;
      }
      else{
            return 0 ; // brghot sad that we chould use 1 and 0 best then 0 and -1  
      }
}
// mzal mkmltch ida kayn bugs 5lihm 76li brk commant ;)