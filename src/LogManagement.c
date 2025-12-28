#include <stdio.h>
#include "../library/project.h"
#include "../library/AuditSecAnalysis.h"
#include "../library/Encryption.h"
#include "../library/LogManagement.h"
#include "../library/MathSecTool.h"
#include <math.h>
#include <string.h>
#include <stdbool.h>
void initLog(struct Log logs[] , int *n ){
    do {
        printf("Enter the number of logs to initialize: ");
        scanf("%d", n);
    } while (*n <= 0);
    
    for (int i = 0 ; i < *n ; i++){
        printf("Enter log %d user: ", i+1);
        scanf("%19s", logs[i].user);
        printf("Enter log %d action: ", i+1);
        scanf("%49s", logs[i].action);
        printf("Enter log %d date (YYYY-MM-DD): ", i+1);
        scanf("%19s", logs[i].date);
        printf("Enter log %d time (HH:MM:SS): ", i+1);
        scanf("%9s", logs[i].time);
        do {
            printf("Enter log %d code [0] info, [1] warning, [2] error: ", i+1);
            scanf("%d", &logs[i].code);
        } while (logs[i].code < 0 || logs[i].code > 2);
    }
}
void displayLogs(struct Log logs[], int n){
    for (int i = 0 ; i < n ; i++ ){
        printf("============================== logs info ===========================\n");
        printf("Log %d user: %s\n", i+1, logs[i].user);
        printf("Log %d action: %s\n", i+1, logs[i].action);
        printf("Log %d date: %s\n", i+1, logs[i].date);
        printf("Log %d time: %s\n", i+1, logs[i].time);
        printf("Log %d code: ", i+1);
        switch (logs[i].code) {
            case 0:
                printf("info\n");
                break;
            case 1:
                printf("warning\n");
                break;
            case 2:
                printf("error\n");
                break;
            default:
                printf("unknown\n");
        }
    }
}
void searchLogsByDate(struct Log logs[] , int n , char date[]){
    printf("Logs on date %s:\n", date);
    for (int i = 0 ; i < n ; i++ ){
        if (strcmp(logs[i].date, date) == 0){
            printf("Log %d user: %s, action: %s, time: %s, code: %d\n",
                   i+1, logs[i].user, logs[i].action, logs[i].time, logs[i].code);
        }
    }
}
int countErrorLogs(struct Log logs[], int n){
    int count = 0; 
    for(int i = 0 ; i < n ; i++){
        if (logs[i].code == 2){
            count++;
        }
    }
    return count;
}
int countBlockedLogs(struct Log logs[], int n){
    int count = 0; 
    for(int i = 0 ; i < n ; i++){
        if (logs[i].code == 1){
            count++;
        }
    }
    return count;
}
void sortLogsByDate(struct Log logs[], int n){
    struct Log temp;
    for (int i = 0 ; i < n-1 ; i++ ){
        for (int j = i+1 ; j < n ; j++ ){
            if (strcmp(logs[i].date, logs[j].date) > 0){
                temp = logs[i];
                logs[i] = logs[j];
                logs[j] = temp;
            }
        }
    }
}
int detectSuspiciousActivity(struct Log logs[], int n, char user[]){
    int count = 0 ;
    for(int i =0 ; i < n ; i++){
        if(strcmp(logs[i].user, user) == 0 && logs[i].code == 1){ // i dont know if we should consider error as suspicious
            count++;
        }
    }
}
float errorRate(struct Log logs[], int n){
    int errorCount = 0 ;
    for (int i = 0 ; i < n ; i++ ){
        if (logs[i].code == 2){
            errorCount++;
        }
    }
    return (float)errorCount / n ;
}