#include <stdio.h>
#include "../library/project.h"
#include "../library/AuditSecAnalysis.h"
#include "../library/Encryption.h"
#include "../library/LogManagement.h"
#include "../library/MathSecTool.h"
#include <math.h>
#include <string.h>
#include <stdbool.h>

bool isEven(int n){
    if ( n % 2  == 0 ){
        return true;
    }else {
        return false ; 
    }
}
int countDigits(int n){
    if ( n == 0 ){
        return 1 ; 
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

bool isPrime(int n){
    int i; 
    if (n <= 1 ){
        return false ;  
    }
    if (n == 2 ){
        return true ; 
    }
    if(n % 2 ==0 ){
        return false ;  
    }
    for (i = 3 ; i*i <= n ; i += 2 ){  
        if ( n % i == 0 ){
            return false ;  
        }
    }
    return true ; 
    
}

int gcd(int a, int b){
    int r ;  
    while ( b != 0){ 
        r = a % b ;
        a = b ;
        b = r ;
    }
    return a ;
}

long long lcm(int a, int b){ 
    return (long long)a*b / gcd(a,b);
}

long long  globalmodExp(long long  base , long long exponent, long long  mod){
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
long long factorial(int n){
    long long fact = 1 ;
    if (n < 0){
        return -1; 
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
        n = -n ; 
    }
    while ( n != 0 ){
        reverse = reverse * 10 + n % 10 ;
        n = n / 10 ;
    }
    return sign * reverse ;
}
bool isPalindromeNumber(int n){
    if( n < 0 ){
        return false ; 
    }
    int reverse = reverseNumber(n);
    if (reverse == n){
        return true ; 
    }else {
        return false ; 
}
}
int sumDivisors(int n){
    int sum = 0 ;
    if( n <= 0 ){
        return -1 ; 
    }
    for ( int i =1 ; i <= n/2 ; i++){
        if (n % i == 0 ){
            sum = sum + i ;
        }

    }
    return sum ;
}

bool isPerfectNumber(int n ){
    if ( n <= 0 ){
        return false ; 
    }
    int sum = sumDivisors(n) - n ; 
    if ( sum == n ){
        return true ; 
    }else {
        return false ;
    }
}

bool isArmstrong(int n){
    if ( n < 0 ){
        return false ; 
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
        return true ; 
    }else {
        return false ; 
    }    

}
int randomNumber(int min, int max){ 
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
void sortAscending(int T[], int n){ 
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
void displayMatrix(struct Matrix M){
    for(int i = 0 ; i < M.n ; i ++){
        for (int j = 0 ; j < M.p ; j++){
            printf("%d ",M.data[i][j]);
        }
        printf("\n");
    }
}
void addMatrices(struct Matrix A, struct Matrix B, struct Matrix *C){
    if (A.n != B.n || A.p != B.p ){
        printf("Matrix A and B need to be the same in size.");
    }
    else {
        C->n = A.n ;
        C->p = B.p ;
        for (int i = 0 ; i < C->n ; i++){
            for (int j = 0 ;j < C->p ;j++){
                C->data[i][j] = A.data[i][j]+B.data[i][j];
            }
        }
    }
}
void multiplyMatrices(struct Matrix A, struct Matrix B, struct Matrix *C) {
    if (A.p != B.n) {
        printf("Error: Matrix multiplication impossible (A columns ≠ B rows)\n");
        return;
    }
    
    C->n = A.n;  
    C->p = B.p;  
    
    for (int i = 0; i < C->n; i++) {
        for (int j = 0; j < C->p; j++) {
            C->data[i][j] = 0;
            for (int k = 0; k < A.p; k++) {
                C->data[i][j] += A.data[i][k] * B.data[k][j];
            }
        }
    }
}

    

void transposeMatrix(struct Matrix A, struct Matrix *T){
    T->n = A.p ; 
    T->p = A.n ; 
    for (int i =0 ; i < T->p ; i ++){
        for (int j = 0 ; j < T->n ; j ++){
            T->data[j][i]=A.data[i][j];
        }
    }
}
int determinant2x2(int A[2][2]){
    return A[0][0]*A[1][1]-A[0][1]*A[1][0];
}
bool isSymmetric(struct Matrix M){
    if (M.n != M.p){
        return false;
    }
    else{
        for(int i = 0 ; i < M.n ; i ++){
            for (int j = 0; j < M.p; j++)
            {
                if(M.data[i][j] != M.data[j][i]){
                    return false ;
                }
            }   
        }
    }
    return true ;
}
bool isIdentity(struct Matrix M){ 
    if (M.n != M.p){
        return false ; 
    }
    else{
        for (int i = 0 ; i < M.n; i ++ ){
            if (M.data[i][i]!=1){
                return false ;
            }
            for (int j = 0; j < M.n; j++)
            {
                if (i != j && M.data [i][j] != 0){
                    return false ;
                }
            }
            
        }
    }
    return true ;
}
// chof ida jatek fikra jdida fkach algo ectbha w5ali l9dima ok ?