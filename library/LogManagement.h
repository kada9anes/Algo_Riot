#ifndef ALGO_PROJECT_H
#define ALGO_PROJECT_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
// logmanagement : 
struct Log {
    char user[20];
    char action[50];
    char date[20];
    char time[10];
    int code;   // 0 info, 1 warning, 2 error
};


#endif 