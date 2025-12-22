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
void encryptXOR(struct Message *m, int key){
      for (int i = 0 ; i < m->length -1; i++ ){
            m->text[i]=m->text[i]^key ;
      }
}
void encryptSubstitution(struct Message *m, char key[26]){
      for(int j = 0 ; j < 26 ; j++){
      if(key[j] >= 97 && key[j] <= 122){
            key[j] = key[j] - 32 ;
      }
      }
      for (int i = 0 ; i < m->length ; i++){
            if (isUppercase(m->text[i])){
                  m->text[i]= key[ m->text[i]-'A'];
            }
            if (isLowercase(m->text[i])){
                  m->text[i]= key[ m->text[i]-'a']+32;
            }
      }

}
int isValidKey(char key[27]) {
    int freq[26] = {0};
    int idx ;

    for (int i = 0; i < 26; i++) {
        char c = key[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))){ 
            return false ;
        }
        if (c >= 65 && c <=90)
          idx = c - 'A';
        else{
          idx = c -'a';
        }
        if (freq[idx] > 0){
            return false;
        }
        freq[idx] = 1;
    }
    return true;
}
int countCharacter(struct Message m, char c){
      int r = 0 ; 
      for (int  i = 0; i < m.length; i++)
      {
            if (m.text[i]== c){
                  r++ ;
            }
      }
      return r ;
}
float coincidenceIndex(struct Message m){
      float r = 0.000000 ;
      int f ;
      toUppercase(&m);
      for (int i = 0; i <=25; i++)
      {
            f = countCharacter(m, i+'A') ;
            r += f * (f - 1 ); 
      }
      if (m.length <= 1)return 0.0 ;
      return r/((m.length-1)*(m.length-2));
}

