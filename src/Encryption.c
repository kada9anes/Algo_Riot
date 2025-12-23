#include <stdio.h>
#include "../library/project.h"
#include <math.h>
#include <string.h>
#include <stdbool.h>
void inputMessage(struct Message *m){
      printf("Enter the message : ");fgets(m->text , sizeof(m->text) , stdin);
      m->length = strlen(m->text);
      if(m->text[m->length -1 ] == '\n'){
            m->text[m->length -1 ] = '\0' ;
            m->length -- ;
      }
}      
void displaymessage(struct Message *m){
      printf("%s \n" , m->text);
}

bool isUppercase(char c){
      if ( c <= 'Z' && c >='A' ){
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
      if ( (c <= 'z' && c >='a') || (c <= 'Z' && c>= 'A') ){
            return true ;
      }
      else{
            return false ; 
      }
}
void toUppercase(struct Message *m ){ 
    for(int i = 0 ; i < m->length ; i++){
      if(m->text[i] >= 'a' && m->text[i] <= 'z'){
            m->text[i] -= ('a' - 'A');  // BASICALLY THE SAME AS 32 
      }
      }

}
void toLowercase(struct Message *m){
      for(int i =0 ; i < m->length ; i++){
            if(isUppercase(m->text[i])){
                  m->text[i] += ('a' - 'A');
            }
      }
}
void removeSpaces(struct Message *m){
      for(int i = 0 ; i < m->length ; i ++){
            int j = i+1 ;
            while (m->text[i]==' ')
            {
                   
                  m->text[i]=m->text[j];
                  m->text[j]=' ';
                  j++ ;     
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
                  m->text[i] =  ( (m->text[i] - 'a' + key + 26) % 26 ) + 'a' ;
            }
            if(isUppercase(m->text[i])){
                  m->text[i] = ( (m->text[i] - 'A' + key + 26) % 26 ) + 'A';
            }
      }

}
void decryptCesar(struct Message *m, int key){
      encryptCesar(m, -key);
}
void encryptXOR(struct Message *m, int key){
      for (int i = 0 ; i < m->length ; i++ ){
            m->text[i]=m->text[i]^key ;
      }
}
void decryptXOR(struct Message *m, int key){ // same as encrypt 
      encryptXOR(m, key);
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
void decryptSubstitution(struct Message *m , char key[26]){

}
bool isValidKey(char key[27]) {
    int freq[26] = {0};
    int idx ;
    if (key == NULL)
        return false;


    for (int i = 0; i < 26; i++) {
        char c = key[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))){ 
            return false ;
        }
        if (c >= 'A' && c <='Z')
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
bool compareMessages(struct Message *m1 , struct Message *m2){


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
void frequencyAnalysis(struct Message *m){
      
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
      return r/((m.length-1)*(m.length-2)); // i think this is false note that you count the length with strlen so it wont include \0 so it was better to write m.length * m.length -1
}

