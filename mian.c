#include <stdio.h>
#include "library/project.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
int main(){ 
  char c = 'a';
  struct Message m={
    .length = 0,
    .text="",
  };
  inputMessage(&m);
  printf("%s",m.text);
  printf("%i",isUppercase(c));
  printf("%i",isUppercase(c));
    
}
     
      