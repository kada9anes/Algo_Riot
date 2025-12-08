#include <stdio.h>
#include "library/project.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
int main(){ 
  struct Matrix A ={
    .data= {
    { 1,  0,  0, 0,  0 },
    { 0,  1,   0,  0,  0 },
    { 0,  0,  1,  0,  0 },
    {  0,   0, 0, 1,  0 },
    {  0,   8,   0,  0,   1 }},
    .n = 5,
    .p = 5,
  };
  /*struct Matrix B ={
    .data={
    {  2,  -3, -10,   3,   1 },
    { -9,   0,  -6,   6,   8 },
    {  6,  -1,   7,  -7,   4 },
    { -3,  -8,  -2,  -4,   3 },
    {  7,   3,   9,  -9,   0 }},
    .n = 5,
    .p = 5,
  }*/
  /*struct Matrix C ={
    .data={},
    .n = 3,
    .p = 3,
  };*/
  //multiplyMatrices(A,B,&C);
  //displayMatrix(C);
  printf("%d", isIdentity(A));
  
    
}
     
      