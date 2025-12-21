#include <stdio.h>
#include "../library/project.h"
#include <math.h>
#include <string.h>
#include <stdbool.h>
void inputMessage(struct Message *m){
      printf("Enter the message ;)");fgets(m->text , sizeof(m->text) , stdin);
      m->length = strlen(m->text);
}
void displaymessage(struct Message *m){
      printf("%s \n" , m->text);
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
void toUppercase(struct Message *m ){ // i dont know how it work but it work 
    for(int i = 0 ; i < m->length ; i++){
      if(m->text[i] >= 97 && m->text[i] <= 122){
            m->text[i] = m->text[i] - 32 ;
      }
      }

}
void reverseMessage(struct Message *m){
      char tmp ; 
      for (int i = 0 ; i < m->length -i  ; i ++){
            tmp = m->text[i];
            m->text[i] = m->text[m->length -1 - i] ;
            m->text[m->length -1 - i] = tmp ;
      }
}
void encryptCesar(struct Message *m, int key){
      for (int i = 0 ; i <m->length ; i++ ){
            if (isLowercase(m->text[i])){
                  m->text[i] =  'a'+(m->text[i] - 'a' + key)%26 ;
            }
            if(isUppercase(m->text[i])){
                  m->text[i] = 'A'+(m->text[i] - 'A' + key)%26 ;
            }
      }

}

