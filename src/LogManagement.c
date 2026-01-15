#include <stdio.h>
#include "../library/project.h"
#include "../library/AuditSecAnalysis.h"
#include "../library/Encryption.h"
#include "../library/LogManagement.h"
#include "../library/MathSecTool.h"
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
void initLogs(struct Log logs[] , int *n ){ // we get time from system not from user 
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int year  = t->tm_year + 1900;
    int month = t->tm_mon + 1;
    int day   = t->tm_mday;
    int hour  = t->tm_hour;
    int min   = t->tm_min;
    int sec   = t->tm_sec;

    do {
        printf("Enter the number of logs to initialize: ");
        scanf("%d", n);
    } while (*n <= 0);
    
    for (int i = 0 ; i < *n ; i++){
        printf("Enter log %d user: ", i+1);
        scanf("%19s", logs[i].user);
        printf("Enter log %d action: ", i+1);
        scanf("%49s", logs[i].action);
        snprintf(logs[i].date, sizeof(logs[i].date) ,"%4d/%2d/%2d", year, month, day);
        snprintf(logs[i].time, sizeof(logs[i].time) ,"%2d:%2d:%2d", hour, min, sec);
        do {
            printf("Enter log %d code [0] info, [1] warning, [2] error: ", i+1);
            scanf("%d", &logs[i].code);
        } while (logs[i].code < 0 || logs[i].code > 2);
    }
}
void addLog(struct Log logs[], int *n, char user[], char action[], int code){
    int i = *n ;
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int year  = t->tm_year + 1900;
    int month = t->tm_mon + 1;
    int day   = t->tm_mday;
    int hour  = t->tm_hour;
    int min   = t->tm_min;
    int sec   = t->tm_sec;
    (*n)++;
    strcpy(logs[i].user,user);
    strcpy(logs[i].action,action);
    logs[i].code = code;
    snprintf(logs[i].date, sizeof(logs[i].date) ,"%04d-%02d-%02d", year, month, day);
    snprintf(logs[i].time, sizeof(logs[i].time) ,"%02d:%02d:%02d", hour, min, sec);

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
void searchLogsByUser(struct Log logs[], int n, char user[]){
    printf("logs of user : %s \n",user);
    for (int i = 0 ;i < n ; i++){
        if (strcmp(logs[i].user,user)==0){
            printf("Log %d user: %s, action: %s, time: %s, code: %d\n", i+1, logs[i].user, logs[i].action, logs[i].time, logs[i].code);
        }

    }
}
void searchLogsByDate(struct Log logs[] , int n , char date[]){
    printf("Logs on date %s:\n", date);
    for (int i = 0 ; i < n ; i++ ){
        if (strcmp(logs[i].date, date) == 0){
            printf("Log %d user: %s, action: %s, time: %s, code: %d\n", i+1, logs[i].user, logs[i].action, logs[i].time, logs[i].code);
        }
    }
}
int countLoginLogs(struct Log logs[], int n){
    int count = 0 ;
    for (int i = 0 ; i < n ; i++ ){
        if (logs[i].code == 0){
            count++;
        }
    } 
    return count ++ ; 
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
void displayLogStats(struct Log logs[], int n){
    printf("=======================logs satats===========================\n ");
    printf("number of logs is : %i",n);
    printf("number of login events is : %i",countLoginLogs(logs , n));
    printf("number of blocked attempts is : %i",countBlockedLogs(logs,n));
    printf("number of error entries : %i",countBlockedLogs(logs,n));

}
void sortLogsByDate(struct Log logs[], int n){ //Selection Sort
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
void sortLogsByUser(struct Log logs[], int n){ //Selection Sort
    struct Log temp;
    for (int i = 0 ; i < n-1 ; i++ ){
        for (int j = i+1 ; j < n ; j++ ){
            if (strcmp(logs[i].user, logs[j].user) > 0){
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
    return count;

}
int dailyConnections(struct Log logs[], int n, char date[]){
    int count = 0 ; 
    for (int i = 0 ; i<n ;i++){
        if (strcmp(logs[i].date ,date)==0){
            count++;
        }
    }
    return count;

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
void exportLogsCSV(struct Log logs[], int n){
    FILE *f = fopen("logs.csv" , "w");
    if(f == NULL){
        printf("Error : cannot create csv file \n");
        return;
    }
    // t3bni hada n7ito fprintf(f , "User,action,date,time,code\n");
    for (int i =0 ; i < n ; i++){
        fprintf(f, "\"%s\",\"%s\",\"%s\",\"%s\",%d\n" , logs[i].user , logs[i].action , logs[i].date , logs[i].time , logs[i].code);
        // print it in the format : "user","action","date","time",code
        //  عدبتني ب ""
    }
    fclose(f);
}
void importLogsCSV(struct Log logs[], int n){
    FILE *f = fopen("logs.csv","r");
    int result ;
    if (f== NULL){
        printf("Error : cannot open csv file \n");
        return;
    }
    for (int i = 0 ; i<n ;i++){
        result = fscanf(f, "\"%49[^\"]\",\"%49[^\"]\",\"%19[^\"]\",\"%19[^\"]\",%d\n", 
                logs[i].user, logs[i].action, logs[i].date, logs[i].time, &logs[i].code);
        if (result == 5) {
            continue; 
        } 
        else if (result == EOF) {
            printf("Warning: End of file reached after successfully reading %d logs.\n", i);
            fclose(f);
            return;
        } 
        else { 
            printf("Error: Malformed log entry found at index %d (only read %d fields).\n", i, result);
            fclose(f);
            return;
        }
    }
    
    fclose(f);
    return;
}

void clearLogs(struct Log logs[], int n){
    for (int i = 0 ; i < n ; i++ ){
        strcpy(logs[i].user, "");
        strcpy(logs[i].action, "");
        strcpy(logs[i].date, "");
        strcpy(logs[i].time, "");
        logs[i].code = -1; // invalid
    }
}
void recentLogs(struct Log logs[], int n, int nb){
    sortLogsByDate(logs , n );
    if (nb > n ){
        displayLogs(logs,n);
    }
    else{
    displayLogs(logs , nb);
    }
}
void archiveLogs(struct Log logs[], int n){
    if (n <= 0) {
        return;
    }
    FILE *f = fopen("logs_archive.txt" , "a");
    if (f == NULL){
        printf("Error : cannot open archive file \n");
        return;
    }
    for(int i =0 ; i < n ;i++){
        fprintf(f, "User: %s | Action: %s | Date: %s | Time: %s | Code: %d\n",
                logs[i].user, 
                logs[i].action, logs[i].date, logs[i].time, logs[i].code);

    }
    fclose(f);
}
void showTopErrors(struct Log logs[], int n) // this is chatgpt code for testing
{
    const int TOP_K = 5;
    if (logs == NULL || n <= 0) {
        printf("No logs available.\n");
        return;
    }

    int count[n];
    int used[n];

    for (int i = 0; i < n; i++) {
        count[i] = 0;
        used[i] = 0;
    }

    /* Count identical ERROR actions */
    for (int i = 0; i < n; i++) {
        if (logs[i].code != 2)   // not an error
            continue;

        if (used[i])
            continue;

        count[i] = 1;
        used[i] = 1;

        for (int j = i + 1; j < n; j++) {
            if (!used[j] &&
                logs[j].code == 2 &&
                strcmp(logs[i].action, logs[j].action) == 0)
            {
                count[i]++;
                used[j] = 1;
            }
        }
    }

    printf("Top %d Error Actions:\n", TOP_K);

    for (int k = 0; k < TOP_K; k++) {
        int maxIdx = -1;
        int maxCount = 0;

        for (int i = 0; i < n; i++) {
            if (count[i] > maxCount) {
                maxCount = count[i];
                maxIdx = i;
            }
        }

        if (maxIdx == -1 || maxCount == 0)
            break;

        printf("[%d] (%d times) Action: %s\n",
               k + 1,
               maxCount,
               logs[maxIdx].action);

        count[maxIdx] = 0;  // prevent re-selection
    }
}
/*void showTopErrors(struct Log logs[], int n){
// I don't know what this function does
}
*/