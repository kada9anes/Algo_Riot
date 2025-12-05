#include <stdio.h>
#include "library/project.h"
int main(){
      int a,b,c ;
      printf("test : "); // for evoid colusion :  poll then edit then posh "best pest derctly edit dont write it in project "
      scanf("%d%d%d",&a,&b,&c);
      printf( "%i",modExp(a,b,c));
    return 0 ;
}