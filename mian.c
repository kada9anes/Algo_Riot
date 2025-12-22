#include "library/project.h"
int main(){ 
  char c = 'a';
  struct Message m={
    .length = 0,
    .text="",
  };
  //every time you write a function pls write that you are the one who wrote it like this : written by koussei
  inputMessage(&m);
  displaymessage(&m);
  printf("%i \n",isUppercase(c));
  printf("%i \n ",isUppercase(c));
}
     
      