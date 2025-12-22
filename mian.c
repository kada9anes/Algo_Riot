#include "library/project.h"
int main(){ 
  char c = 'a';
  struct Message m={
    .length = 0,
    .text="",
  };
  
  inputMessage(&m);
  displaymessage(&m);
  printf("%i \n",isUppercase(c));
  printf("%i \n ",isUppercase(c));
}
     
      