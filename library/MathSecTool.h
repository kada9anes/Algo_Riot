#ifndef MATHSECTOOL_H
#define MATHSECTOOL_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//MathSecTool
struct Matrix{
int data[10][10];
int n, p;
};
bool isEven(int n);
int countDigits(int n);
bool isPrime(int n);
int gcd(int a, int b);
long long lcm(int a, int b);
long long globalmodExp(long long  base , long long exponent, long long  mod);
long long factorial(int n);
int sumDigits(int n);
int reverseNumber(int n);
bool isPalindromeNumber(int n);
int sumDivisors(int n);
bool isPerfectNumber(int n );
bool isArmstrong(int n);
int randomNumber(int min, int max);
int sumArray(int T[], int n);
float averageArray(int T[], int n);
int maxArray(int T[], int n);
int minArray(int T[], int n);
void sortAscending(int T[], int n);
void displayMatrix(struct Matrix M);
void addMatrices(struct Matrix A, struct Matrix B, struct Matrix *C);
void multiplyMatrices(struct Matrix A, struct Matrix B,struct Matrix *C);
void transposeMatrix(struct Matrix A, struct Matrix *T);
int determinant2x2(int A[2][2]);
bool isSymmetric(struct Matrix M);
bool isIdentity(struct Matrix M);
#endif