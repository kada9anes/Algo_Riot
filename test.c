#include <stdio.h>
#include <stdbool.h>
#include<math.h>
#include<time.h>
#include<string.h>

typedef long long ll;
int simplesumofdiagonal(int k){
    int sum=1;
    for(int i=3;i<=k ; i+=2){
     // Find largest palindrome ma
        sum += i*i + i*i-(i-1) + i*i-2*(i-1) + i*i-3*(i-1);

    }
    return sum;
}
int sumofdiagonal(int array[][100],int n){
    int sum=0;int i=0;int j=n-1;
    while(i<n && j>=0){
        sum += array[i][j];
        i++;
        j--;
    }
    return sum;

}
bool isPalindrome(ll n) {
    ll orig = n, reversed = 0;
    while (n > 0) {
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }
    return orig == reversed;
}
int divisor(int n , int k){
    int counter =0;
    while(n > 0){
        n=n-k;
        counter++;

    }
    if (n==0){

        return k;
    }
    else{
        return -1;
    }
}
int reverse(int n){
    int reversed =0;
    while(n>0){
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }
    return reversed;
}
bool findmysterious(int n){
    int reversed = reverse(n);
    int squarenumber = n * n;
    int squarereversed = reversed * reversed;
    if (squarenumber == reverse(squarereversed)){
        return true;
    }else{
        return false;
    }
}
int sumProperDivisors(int n) {
    int sum = 0;
    for (int i = 1; i <= n / 2; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    return sum;
}
bool isAbundant(int n) {
    return sumProperDivisors(n) > n;
}
bool isDeficient(int n) {
    return sumProperDivisors(n) < n;
}
bool isPerfect(int n) {
    return sumProperDivisors(n) == n;
}
int classifyNumber(int n) {
    if (isAbundant(n)) return 1;   // Abundant
    if (isDeficient(n)) return -1;
    if (superabundant(n)) return 2; // Deficient
    return 0;                      // Perfect
}

bool superabundant(int n ){
    int sumdivisor = sumProperDivisors(n);
    int ratio = (float)sumdivisor / n;
    for(int i=1 ; i< n ; i++){
        int sumdivisor_i = sumProperDivisors(i);
        float ratio_i = (float)sumdivisor_i / i;
        if (ratio_i >= ratio){
            return false;
        }
    }
    return true;  
}
int smallestabudant(){
    for(int i=1 ; 100 ; i++){
        if (isAbundant(i)){
            return i;
        }
    }
}
void findabundanttriplet(int limit){
    for(int i =1 ; i<= limit ; i++){
        if( (isAbundant(i)) && isAbundant(i+1) && isAbundant(i+2)){
            printf("Abundant triplet found: %d, %d, %d\n", i, i+1, i+2);
            return 0;
        }
    }
}
int main() {

     /*int k;
     printf("Enter k: ");
     scanf("%d", &k);

     ll max = 0;
     ll factor1 = 0, factor2 = 0;
     ll start = 1;
     for (int i = 1; i < k; i++) start *= 10;
     ll end = start * 10 - 1;

     for (ll i = end; i >= start; i--) {
        for (ll j = i; j >= start; j--) {
            ll product = i * j;
            if (product <= max) break; // skip smaller products
            if (isPalindrome(product)) {
                max = product;
                factor1 = i;
                factor2 = j;
            }
        }
     }

     printf("Largest palindrome = %lld = %lld * %lld\n", max, factor1, factor2);
     */
    
   
     /* //for divisor function test
         printf("give a njumber to divide: "); 
       int n,max_divisor=0;
      scanf("%d", &n);
      for(int k=1; k<=n ; k+=2){
        int result = divisor(n , k);
        if(result != -1){
            if (result >= max_divisor){
                max_divisor = k;
            }
        }
     }
     printf("Maximum odd divisor count = %d\n", max_divisor);
    */
    
    /*  //for simplesumofdiagonal test
     printf("Enter size of matrix (n x n): ");
     int n;
     scanf("%d", &n);
    
     int matrix[n][n];
    
     int diagonal_sum = sumofdiagonal(matrix, n);
     printf("Sum of secondary diagonal: %d\n", diagonal_sum);
    */
  /*  //for simplesumofdiagonal test
     int n;
     printf("give the number n : ");
     scanf("%d", &n);
     int sum = simplesumofdiagonal(n);
     printf("the sum of diagonals is : %d \n", sum);
   */ 
  /*  //for mysterious number test
    int n;
    printf("give a number to check for all numbers under n if mysterious number: ");
    scanf("%d", &n);
    for(int i=1 ; i<=n ; i++){
        if (findmysterious(i)){
            printf("%d is a mysterious number\n", i);
        }
    }
        */ //
   return 0;
}
