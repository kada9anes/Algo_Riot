#include <stdio.h>
#include "../library/project.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>
int isEven(int n){
    if ( n % 2  == 0 ){// detction of eveness
        return 1;
    }else {
        return -1 ; // note that this return int not bool
    }
}
int countDigits(int n){
    if ( n == 0 ){
        return 1 ; // zero has one digit
    }
    if ( n < 0 ){
        n = -n ; 
    }
    int count = 0 ;
    while ( n != 0 ){
        n = n / 10 ;
        count++ ;
    }
    return count ;
}

int isPrime(int n){
    int i; 
    if (n <= 1 ){
        return -1 ; // not prime 
    }
    if (n == 2 ){
        return 1 ; // prime 
    }
    if(n % 2 ==0 ){
        return -1 ; // not prime 
    }
    for (i = 3 ; i*i <= n ; i += 2 ){ // check from 3 to sqrt(n) 
        if ( n % i == 0 ){
            return -1 ; // not prime 
        }
    }
    return 1 ; // prime
    
}
int gcd(int a, int b){
    int r ;  // get gcd using euclide algorithm
    while ( b != 0){ 
        r = a % b ;
        a = b ;
        b = r ;
    }
    return a ;
}
int lcm(int a, int b){ 
    return a*b / gcd(a,b);
}
long long  globalmodExp(long long  base , long long exponent, long long  mod){ //handles big numbers but in project sheet say int 
    long long  result = 1 ; 
    base = base % mod;
    while (exponent > 0){
        if (exponent % 2 ==1){
            result = (result * base) % mod;
        }
        base = base * base % mod;
        exponent = exponent /2;

    }
    return result;
}
int modExp(int base , int exponent, int mod){ //handles small numbers
    int result = 1 ; 
    base = base % mod;
    while (exponent > 0){
        if (exponent % 2 ==1){
            result = (result * base) % mod;
        }
        base = base * base % mod;
        exponent = exponent /2;

    }
    return result;
}
int factorial(int n){
    int fact = 1 ;
    if (n < 0){
        return -1; //not defined for negative 
    }
    if (n == 0){
        return 1 ; 
    }
    for(int i = n ; i >= 1 ; i--){
        fact = fact * i ;
    }
    return fact ;
}
int sumDigits(int n){
    int sum = 0; 
    while (n != 0){
        sum = sum + n % 10 ;
        n = n / 10 ;
    }
    return sum ;
}
int reverseNumber(int n){
    int reverse = 0 ;
    int sign = 1 ;
    if(n < 0){
        sign = -1;
        n = -n ; // make it positive for reversal
    }
    while ( n != 0 ){
        reverse = reverse * 10 + n % 10 ;
        n = n / 10 ;
    }
    return sign * reverse ;
}
int isPalindrome(int n){
    if( n < 0 ){
        return -1 ; // negative numbers are not palindrome
    }
    int reverse = reverseNumber(n);
    if (reverse == n){
        return 1 ; // is palindrome
    }else {
        return -1 ; // not palindrome
}
}
int sumDivisors(int n){
    int sum = 0 ;
    if( n <= 0 ){
        return -1 ; // not defined for non positive numbers
    }
    for ( int i =1 ; i <= n/2 ; i++){
        if (n % i == 0 ){
            sum = sum + i ;
        }

    }
    return sum ;
}
int isPerfectNumber(int n ){
    if ( n <= 0 ){
        return -1 ; // not defined for non positive numbers
    }
    int sum = sumDivisors(n) - n ; // sumDivisors includes the number itself
    if ( sum == n ){
        return 1 ; // is perfect number
    }else {
        return -1 ; // not perfect number
    }
}
int isArmstrong(int n){
    if ( n < 0 ){
        return -1 ; // not defined 
    }
    int numDigits = countDigits(n);
    int sum = 0 ;
    int save = n ;
    while( n!= 0){
        int dight = n % 10 ;
        int power = pow(dight , numDigits); ;
        sum = sum + power ;
        n = n / 10 ;
    }
    if ( sum == save ){
        return 1 ; // is armstrong
    }else {
        return -1 ; // not armstrong
    }    

}
int randomNumber(int min, int max){ //note : include <stdlib.h> and <time.h> in header
    srand(time(0)); // this is the seed for rand function
    return (rand() % (max - min + 1)) + min ;

}
int sumArray(int T[], int n){
    int sum = 0; 
    for (int i =0 ; i < n ; i++){
        sum += T[i];

    }
    return sum ;
}
float averageArray(int T[], int n){
    return (float) sumArray(T,n) / n ;
}
int maxArray(int T[], int n){
    int max = T[0];
    for ( int i =1 ; i < n ; i++){
        if ( T[i] > max ){
            max = T[i];
        }
    }
    return max ;
}
int minArray(int T[], int n){
    int min = T[0];
    for ( int i =1 ; i < n ; i++){
        if ( T[i] < min ){
            min = T[i];
        }
    }
    return min ;
}
void sortAscending(int T[], int n){ //sort using selection sort algorithm
    for(int i = 0; i < n-1; i++){
        int minIndex = i;
        for(int j = i+1; j < n; j++){
            if(T[j] < T[minIndex])
                minIndex = j;
        }
        if(minIndex != i){
            int temp = T[i];
            T[i] = T[minIndex];
            T[minIndex] = temp;
        }
    }
}

// 5lili chwia 5dmthm g3 rak 
// a5dm w7da b w7da (w7da liya wtda lik ) 5alili brk 