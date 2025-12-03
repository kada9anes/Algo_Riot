#include <stdio.h>
#include "../library/project.h"
int isEven(int n){
    printf("Enter number n : "); scanf("%i", &n);
    if ( n % 2  == 0 ){// detction of eveness
        return 1;
    }
    
}
int isPrime(int n){
    int i; 
    printf("Enter number n : "); scanf("%i", &n);
    for (i = 2 ; i <= n/2 ; i++){   // ditection if n isn't prime 
        if ( n % i == 0  ){
            return 0 ; 
            break;
        }
        
    }
    if ( n % i != 0 || n == 2){ // true for n is prime 
        return 1 ;
    }
}
int gcd(int a, int b){
    int i;
    printf ("Enter number a and b to combute gcd(a;b)");scanf("%i;%i",&a,&b);
    if (a >= b ){
        for (i = b ; i >=2 ; i-- ){ 
            if (a % i == 0 && b % i ==0 ){ // start from a because a>b find n : n / b end n / a , n howa bigest 
                break;
            }
        }
    } 
    else{
        for (i = a ; i >=2 ; i-- ){// start from b because b>a find  n : n / b end n / a ,n howa bigest
            if (a % i == 0 && b % i ==0 ){
                break;
            }
        }
    } 
   
    return i ;
    
}
int lcm(int a, int b){
    printf("Enter tow number to compute LCM(a;b)");scanf("%i;%i",a ,b); // hadi bayna 
    return a*b / gcd(a,b);
}
int modExp(int base, int exp, int mod){
    int tmp ; 
    scanf("%d%d%d",base,exp,mod);
    tmp = base ; 
    for (int i = 2 ; i <= exp ; i++ ){
        base = tmp * base ; 
    }
    return base % mod ; 

}
