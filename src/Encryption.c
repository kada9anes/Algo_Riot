#include <stdio.h>
#include "../library/project.h"
#include <math.h>
void inputMessage(struct Message m[]){
      printf("Enter the length of your massage ;)");scanf("%i",&m->length);
      printf("Enter the message ;)");scanf("%s",&m->text );
}
void displaymessage(struct Message m[]){
      printf("%s \n" , &m->text);
}

bool isUppercase(char c){
      if ( c <= 90 && c >=65 ){
            return true ;
      }
      else{
            return false ; // bool is better
      }
}
// for you
bool isLowercase(char c ){ // not tested
      if(c >= 'a' && c <= 'z'){
            return true ;
      }else{
            return false ;
      }
}

bool isAlphabetic(char c){
      if ( (c <= 90 && c >=65) || (c <= 122 && c>= 97) ){
            return true ;
      }
      else{
            return false ; // brghot sad that we chould use 1 and 0 best then 0 and -1  
      }
}
void toUppercase(struct Message m[] ){
    for(int i = 0 ; i < m. ; i++){
      if()
    }
}