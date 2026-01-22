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
    
    

    int tempN = -1;
    do {
        printf("Enter the number of logs to initialize (0-%d): ", MAX_LOGS);
        if (scanf("%d", &tempN) != 1) {
            while (getchar() != '\n'); 
            tempN = -1;
            continue;
        }
    } while (tempN < 0 || tempN > MAX_LOGS);
    *n = tempN;
    
    for (int i = 0 ; i < *n ; i++){
     time_t now = time(NULL);
     struct tm *t = localtime(&now);
     int year  = t->tm_year + 1900;
     int month = t->tm_mon + 1;
     int day   = t->tm_mday;
     int hour  = t->tm_hour;
     int min   = t->tm_min;
     int sec   = t->tm_sec;
        while(getchar() != '\n');

        printf("Enter log %d user: ", i+1);
        fgets(logs[i].user, sizeof(logs[i].user), stdin);
        logs[i].user[strcspn(logs[i].user, "\n")] = '\0';
        printf("Enter log %d action: ", i+1);
         fgets(logs[i].action, sizeof(logs[i].action), stdin);
        logs[i].action[strcspn(logs[i].action, "\n")] = '\0';
    
        snprintf(logs[i].date, sizeof(logs[i].date) ,"%04d-%02d-%02d", year, month, day);
        snprintf(logs[i].time, sizeof(logs[i].time) ,"%02d:%02d:%02d", hour, min, sec);
        do {
            printf("Enter log %d code [0] info, [1] warning, [2] error: ", i+1);
            if (scanf("%d", &logs[i].code) != 1) {
                while (getchar() != '\n'); 
                logs[i].code = -1;
                continue;
            }
        } while (logs[i].code < 0 || logs[i].code > 2);
        while(getchar() != '\n');

    }
}
void addLog(struct Log logs[], int *n, char user[], char action[], int code){
    if (*n >= MAX_LOGS) {
        printf("Error: Log array is full. Cannot add more logs.\n");
        return;
    }
    int i = *n ;
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int year  = t->tm_year + 1900;
    int month = t->tm_mon + 1;
    int day   = t->tm_mday;
    int hour  = t->tm_hour;
    int min   = t->tm_min;
    int sec   = t->tm_sec;
    
    strcpy(logs[i].user,user);
    strcpy(logs[i].action,action);
    logs[i].code = code;
    snprintf(logs[i].date, sizeof(logs[i].date) ,"%04d-%02d-%02d", year, month, day);
    snprintf(logs[i].time, sizeof(logs[i].time) ,"%02d:%02d:%02d", hour, min, sec);
    (*n)++;
}
void displayLogs(struct Log logs[], int n){
    printf("============================== logs info ===========================\n");
    for (int i = 0 ; i < n ; i++ ){
        printf("Log %d : ----------------\n", i+1);
        printf("user: %s\n", logs[i].user);
        printf("action: %s\n", logs[i].action);
        printf("date: %s\n",  logs[i].date);
        printf("time: %s\n", logs[i].time);
        printf("code: ");
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
    return count;
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
    printf("number of logs is : %i \n",n);
    printf("number of login events is : %i \n",countLoginLogs(logs , n));
    printf("number of blocked attempts is : %i\n",countBlockedLogs(logs,n));
    printf("number of error entries : %i \n",countBlockedLogs(logs,n));

}
void sortLogsByDate(struct Log logs[], int n){ //Selection Sort
    struct Log temp;
    for (int i = 0 ; i < n-1 ; i++ ){
        for (int j = i+1 ; j < n ; j++ ){
        int date_cmp = strcmp(logs[i].date, logs[j].date);    
            if (date_cmp > 0) {
                temp = logs[i];
                logs[i] = logs[j];
                logs[j] = temp;
            }
            else if (date_cmp == 0 && strcmp(logs[i].time, logs[j].time) > 0) {
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
        if(strcmp(logs[i].user, user) == 0 && logs[i].code == 1){ // i dont know if we should consider error as suspicious \\ no 
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
void exportLogsCSV(struct Log logs[], int n) {
    FILE *f = fopen("logs.csv", "w");
    if (f == NULL) {
        printf("Error: cannot create csv file\n");
        return;
    }
    
    // Write header
    fprintf(f, "User,Action,Date,Time,Code\n");
    
    for (int i = 0; i < n; i++) {
        fprintf(f, "\"%s\",\"%s\",\"%s\",\"%s\",%d\n", 
                logs[i].user, logs[i].action, logs[i].date, logs[i].time, logs[i].code);
    }
    
    fclose(f);
    printf("Exported %d logs to logs.csv\n", n);
}

void importLogsCSV(struct Log logs[], int *n) {  
    FILE *f = fopen("logs.csv", "r");
    if (f == NULL) {
        printf("Error: cannot open csv file\n");
        return;
    }
    char header[256];
    if (fgets(header, sizeof(header), f) == NULL) {
        printf("Error: CSV file is empty\n");
        fclose(f);
        return;
    }
    int count = 0;
    int result;
    while (count < MAX_LOGS) {
        result = fscanf(f, "\"%49[^\"]\",\"%99[^\"]\",\"%19[^\"]\",\"%19[^\"]\",%d\n", 
                        logs[count].user, logs[count].action, logs[count].date, 
                        logs[count].time, &logs[count].code);
        
        if (result == EOF) {
            break; 
        } 
        else if (result != 5) {
            printf("Error: Malformed entry at line %d (read %d fields)\n", count + 2, result);
            break;
        }
        
        count++;
    }
    
    *n = count; 
    fclose(f);
    printf("Imported %d logs from logs.csv\n", count);
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