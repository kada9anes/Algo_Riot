#ifndef LOG_MANAGEMENT_H
#define LOG_MANAGEMENT_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define MAX_LOGS 500
// logmanagement : 
struct Log{
    char user[20];
    char action[50];
    char date[40];
    char time[10];
    int code;   // 0 info, 1 warning, 2 error
};
void initLogs(struct Log logs[] , int *n );
void addLog(struct Log logs[], int *n, char user[], char action[], int code);
void displayLogs(struct Log logs[], int n);
void searchLogsByUser(struct Log logs[], int n, char user[]);
void searchLogsByDate(struct Log logs[] , int n , char date[]);
int countLoginLogs(struct Log logs[], int n);
int countErrorLogs(struct Log logs[], int n);
int countBlockedLogs(struct Log logs[], int n);
void displayLogStats(struct Log logs[], int n);
void sortLogsByDate(struct Log logs[], int n);
void sortLogsByUser(struct Log logs[], int n);
int detectSuspiciousActivity(struct Log logs[], int n, char user[]);
int dailyConnections(struct Log logs[], int n, char date[]);
float errorRate(struct Log logs[], int n);
void exportLogsCSV(struct Log logs[], int n);
void importLogsCSV(struct Log logs[], int *n);
void clearLogs(struct Log logs[], int n);
void recentLogs(struct Log logs[], int n, int nb);
void archiveLogs(struct Log logs[], int n);
void showTopErrors(struct Log logs[], int n);

#endif 