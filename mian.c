#include <stdio.h>
#include "library/project.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
int main(){ 
  struct Matrix A ={
    .data={{1,2,6,13},{1,3,15,44},{4,5,3,3}},
    .n = 3,
    .p = 4,
  };
  struct Matrix B ={
    .data={{1,1},{1,1},{1,1}},
    .n = 3,
    .p = 2,
  };
  struct Matrix C ={
    .data={},
    .n = 3,
    .p = 4,
  };
  displayMatrix(A);
  transposeMatrix(A,&C);
  displayMatrix(C);
    
    
}
     
      