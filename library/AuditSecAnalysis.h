#ifndef ALGO_PROJECT_H
#define ALGO_PROJECT_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
// AuditSecAnalysis : 
struct User{
      char name[128];
      char password[128];
      int role; // 0: user, 1: admin
      int state; // 0: active, 1: blocked
};

#endif

void NewFunction(struct User users[]);
