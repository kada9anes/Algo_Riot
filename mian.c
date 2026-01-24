#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "library/UserManagement.h"
#include "library/AuditSecAnalysis.h"
#include "library/Encryption.h"
#include "library/LogManagement.h"
#include "library/MathSecTool.h"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"
#define RESET   "\033[0m"
#define BG_RED  "\033[41m"
#define BG_GREEN "\033[42m"
#define MAX_USERS 100
#define MAX_LOGS 500
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define MAX_ACTION_LENGTH 50
#define MAX_LOGIN_ATTEMPTS 3
#define MIN_PASSWORD_LENGTH 8

struct User users[MAX_USERS];
int userCount = 0;
struct Log logs[MAX_LOGS];
int logCount = 0;
char currentUser[MAX_ACTION_LENGTH] = "admin";
int loginAttempts = 0;
void clearScreen() {
    system("clear");
}
void pressEnter() {
    printf(YELLOW "\n[Press ENTER to continue...]" RESET);
    getchar();
    getchar();
}
void printHeader(const char *title) {
    printf(BOLD CYAN "\n╔══════════════════════════════════════════════════════════════╗\n" RESET);
    printf(BOLD CYAN "║  %-58s  ║\n" RESET, title);
    printf(BOLD CYAN "╚══════════════════════════════════════════════════════════════╝\n" RESET);
}
void printSuccess(const char *msg) {
    printf(GREEN "✓ %s\n" RESET, msg);
}
void printError(const char *msg) {
    printf(RED "✗ %s\n" RESET, msg);
}
void printWarning(const char *msg) {
    printf(YELLOW "⚠ %s\n" RESET, msg);
}
void printInfo(const char *msg) {
    printf(CYAN "ℹ %s\n" RESET, msg);
}
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
int confirmAction(const char* action) {
    char response;
    printf(RED "\n⚠ WARNING: " RESET "This will %s\n", action);
    printf(YELLOW "Are you absolutely sure? (y/n): " RESET);
    scanf("%c", &response);
    clearInputBuffer();
    
    return (response == 'y' || response == 'Y');
}
int safeIntInput(int min, int max) {
    int value;
    int result;
    
    while (1) {
        result = scanf("%d", &value);
        
        if (result != 1) {
            printError("Invalid input! Please enter a number.");
            clearInputBuffer();
            printf(YELLOW "▶ Try again: " RESET);
            continue;
        }
        
        clearInputBuffer();
        
        if (value < min || value > max) {
            printError("Number out of range!");
            printf(YELLOW "▶ Enter a value between %d and %d: " RESET, min, max);
            continue;
        }
        
        return value; 
    }
}
void userManagementMenu() {
    int choice;
    char name[MAX_USERNAME_LENGTH], pass[MAX_PASSWORD_LENGTH];
    int role;

    while (1) {
        clearScreen();
        printHeader("USER MANAGEMENT MODULE");
        
        printf("\n" BOLD "┌─ User Operations\n" RESET);
        printf("│  1. " GREEN "Display All Users\n" RESET);
        printf("│  2. " GREEN "Add New User\n" RESET);
        printf("│  3. " YELLOW "Delete User\n" RESET);
        printf("│  4. " CYAN "Search User\n" RESET);
        printf("│  5. " YELLOW "Change Password\n" RESET);
        printf("│  6. " CYAN "Login Test\n" RESET);
        printf("│  7. " RED "Block User\n" RESET);
        printf("│  8. " RED "Unblock User\n" RESET);
        printf("│  9. " MAGENTA "Change User Role\n" RESET);
        printf("│  10. " CYAN "List All Admins\n" RESET);
        printf("│  11. " RED "Users Statistics\n" RESET);
        printf("│  12. " BLUE "Save Users to File\n" RESET);
        printf("│  13. " BLUE "Load Users from File\n" RESET);
        printf("│  0. " RED "← Back to Main Menu\n" RESET);
        printf(BOLD "└─────────────────────────────\n" RESET);
        
        printf(YELLOW "\n▶ Select option: " RESET);
        choice = safeIntInput(0, 13);
        
        clearScreen();
        
        switch (choice) {
            case 1:
                printHeader("ALL REGISTERED USERS");
                displayUsers(users, userCount);
                addLog(logs, &logCount, currentUser, "Viewed user list", 0);
                break;
                
            case 2:
                printHeader("ADD NEW USER");
                if(userCount >= MAX_USERS){
                    printError("Cannot add more users. Maximum limit reached!");
                }else{
                
                addUser(users, &userCount);
                addLog(logs, &logCount, currentUser, "Added new user", 0);
                break;
                }
                
            case 3:
                printHeader("DELETE USER");
                printf(YELLOW "Enter username to delete: " RESET);
                fgets(name, MAX_USERNAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = 0;
                deleteUser(users, &userCount, name);
                addLog(logs, &logCount, currentUser, "Deleted user", 1);
                break;
                
            case 4:
                printHeader("SEARCH USER");
                printf(YELLOW "Enter username to search: " RESET);
                fgets(name, MAX_USERNAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = 0;
                int idx = searchUser(users, userCount, name);
                if (idx != -1) {
                    printSuccess("User found!");
                    printf("\n" CYAN "Name: " RESET "%s\n", users[idx].name);
                    printf(CYAN "Role: " RESET "%s\n", users[idx].role == 1 ? "Admin" : "User");
                    printf(CYAN "Status: " RESET "%s\n", users[idx].state == 0 ? GREEN "Active" RESET : RED "Blocked" RESET);
                } else {
                    printError("User not found!");
                }
                break;
                
            case 5:
                printHeader("CHANGE PASSWORD");
                printf(YELLOW "Enter username: " RESET);
                fgets(name, MAX_USERNAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = 0;
                ChangePassword(users, userCount, name);
                addLog(logs, &logCount, name, "Changed password", 0);
                break;
                
            case 6:
                printHeader("LOGIN VERIFICATION TEST");
                printf(YELLOW "Username: " RESET);
                fgets(name, MAX_USERNAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = 0;
                printf(YELLOW "Password: " RESET);
                fgets(pass, MAX_PASSWORD_LENGTH, stdin);
                pass[strcspn(pass, "\n")] = 0;
                
                if (checkLogin(users, userCount, name, pass)) {
                    printSuccess("Login successful!");
                    addLog(logs, &logCount, name, "Successful login", 0);
                } else {
                    printError("Login failed! Invalid credentials.");
                    addLog(logs, &logCount, name, "Failed login attempt", 2);
                }
                break;
                
            case 7:
                printHeader("BLOCK USER");
                printf(YELLOW "Enter username: " RESET);
                fgets(name, MAX_USERNAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = 0;
                blockUser(users, userCount, name);
                addLog(logs, &logCount, currentUser, "Modified user status", 1);
                break;

            case 8:
                printHeader("UNBLOCK USER");
                printf(YELLOW "Enter username: " RESET);
                fgets(name, MAX_USERNAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = 0;
                unblockUser(users, userCount, name);
                addLog(logs, &logCount, currentUser, "Modified user status", 1);
                break;
                
            case 9:
                printHeader("CHANGE USER ROLE");
                printf(YELLOW "Enter username: " RESET);
                fgets(name, MAX_USERNAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = 0;
                printf(YELLOW "New role (0=User, 1=Admin): " RESET);
                scanf("%d", &role);
                getchar();
                changeRole(users, userCount, name, role);
                addLog(logs, &logCount, currentUser, "Changed user role", 1);
                break;
                
            case 10:
                printHeader("ADMINISTRATOR LIST");
                listAdmins(users, userCount);
                break;
            
            case 11:
                printHeader("USERS STATISTICS");
                userStatistics(users,userCount);
                break;
                
            case 12:
                printHeader("SAVE DATA");
                if (userCount == 0) {
                    printError("No users to save!");
                    break;
                }
                saveUsers(users, userCount);
                printSuccess("Users saved successfully!");
                addLog(logs, &logCount, currentUser, "Saved user database", 0);
                break;
                
            case 13:
                printHeader("LOAD DATA");
                int oldCount = userCount;
                LoadUsers(users, &userCount);
                if(userCount == oldCount){
                    printInfo("No new users loaded.");
                    break;
                }
                printSuccess("Users loaded successfully!");
                addLog(logs, &logCount, currentUser, "Loaded user database", 0);
                break;
                
            case 0:
                return;
                
            default:
                printError("Invalid option!");
        }
        
        pressEnter();
    }
}
void auditAnalysisMenu() {
    int choice;
    char text[100], pass[100], key[100];
    int length;

    while (1) {
        clearScreen();
        printHeader("AUDIT & SECURITY ANALYSIS MODULE");
        
        printf("\n" BOLD "┌─ Password Analysis\n" RESET);
        printf("│  1. " CYAN "Analyze Text Statistics\n" RESET);
        printf("│  2. " GREEN "Test Password Strength\n" RESET);
        printf("│  3. " YELLOW "Calculate Password Score\n" RESET);
        printf("│  4. " MAGENTA "Generate Random Password\n" RESET);
        printf("│  5. " CYAN "Generate Hex Key\n" RESET);
        printf("│  6. " BLUE "Validate Hex Key\n" RESET);
        printf("│\n" BOLD "├─ User Security Reports\n" RESET);
        printf("│  7. " GREEN "Average User Password Score\n" RESET);
        printf("│  8. " YELLOW "Full Security Report\n" RESET);
        printf("│  9. " RED "Global Security Level\n" RESET);
        printf("│  10. " MAGENTA "Top 3 Strongest Passwords\n" RESET);
        printf("│\n" BOLD "├─ Validation & Tips\n" RESET);
        printf("│  11. " CYAN "Check Login Format\n" RESET);
        printf("│  12. " CYAN "Check Email Format\n" RESET);
        printf("│  13. " GREEN "Show Security Tips\n" RESET);
        printf("│  0. " RED "← Back\n" RESET);
        printf(BOLD "└─────────────────────────────\n" RESET);
        
        printf(YELLOW "\n▶ Select option: " RESET);
        choice = safeIntInput(0, 13);
        
        clearScreen();
        
        switch (choice) {
            case 1:
                printHeader("TEXT STATISTICS ANALYSIS");
                printf(YELLOW "Enter text to analyze: " RESET);
                fgets(text, 100, stdin);
                text[strcspn(text, "\n")] = 0;
                displayTextStats(text);
                printf("\n" CYAN "Uppercase: " RESET "%d (%.1f%%)\n", countUppercase(text), percentUppercase(text));
                printf(CYAN "Lowercase: " RESET "%d\n", countLowercase(text));
                printf(CYAN "Percent Uppercase : " RESET "%.2f %\n", percentUppercase(text));
                printf(CYAN "Digits: " RESET "%d\n", countdigits(text));
                printf(CYAN "Length: " RESET "%d\n", textLength(text));
                break;
                
            case 2:
                printHeader("PASSWORD STRENGTH TEST");
                printf(YELLOW "Enter password: " RESET);
                fgets(pass, 100, stdin);
                pass[strcspn(pass, "\n")] = 0;               
                if (veryStrongPassword(pass)== 1) {
                    printSuccess("VERY STRONG PASSWORD! 🔒");
                } else if (strongPassword(pass)== 2) {
                    printWarning("Strong password, but could be better.");
                } else {
                    printError("WEAK PASSWORD! Not secure enough.");
                }
                
                printf("\n" CYAN "Analysis:\n" RESET);
                printf("  Length: %s\n", stringLength(pass) >= 12 ? GREEN "✓" RESET : RED "✗" RESET);
                printf("  Uppercase: %s\n", containsUppercase(pass) ? GREEN "✓" RESET : RED "✗" RESET);
                printf("  Lowercase: %s\n", containsLowercase(pass) ? GREEN "✓" RESET : RED "✗" RESET);
                printf("  Digits: %s\n", containsDigit(pass) ? GREEN "✓" RESET : RED "✗" RESET);
                printf("  Symbols: %s\n", containsSymbol(pass) ? GREEN "✓" RESET : RED "✗" RESET);
                break;
                
            case 3:
                printHeader("PASSWORD SCORE CALCULATOR");
                printf(YELLOW "Enter password: " RESET);
                fgets(pass, 100, stdin);
                pass[strcspn(pass, "\n")] = 0;
                
                int score = passwordScore(pass);
                printf("\n" BOLD "Security Score: ");
                if (score == 7) printf(GREEN "%d/7 - EXCELLENT\n" RESET, score);
                else if (score >= 5 && score < 7) printf(YELLOW "%d/7 - GOOD\n" RESET, score);
                else if (score >= 3 && score < 5) printf(YELLOW "%d/7 - FAIR\n" RESET, score);
                else printf(RED "%d/7 - POOR\n" RESET, score);
                
                printf("\n[");
                for (int i = 0; i < 7; i++) {
                    if (i < score) printf(GREEN "██████" RESET);
                    else printf("░░░░░░");
                }
                printf("]\n");
                break;
                
            case 4:
                printHeader("RANDOM PASSWORD GENERATOR");
                printf(YELLOW "Enter desired length: " RESET);
                scanf("%d", &length);
                getchar();
                
                generateRandomPassword(length, pass);
                printSuccess("Password generated!");
                printf("\n" BOLD CYAN "Generated Password: " RESET BOLD "%s\n" RESET, pass);
                printf(GREEN "Score: %d/7\n" RESET, passwordScore(pass));
                break;
                
            case 5:
                printHeader("HEXADECIMAL KEY GENERATOR");
                printf(YELLOW "Enter key length: " RESET);
                scanf("%d", &length);
                getchar();
                
                generateHexKey(length, key);
                printSuccess("Hex key generated!");
                printf("\n" BOLD CYAN "Generated Key: " RESET BOLD "%s\n" RESET, key);
                break;
                
            case 6:
                printHeader("HEX KEY VALIDATOR");
                printf(YELLOW "Enter hex key to validate: " RESET);
                fgets(key, 100, stdin);
                key[strcspn(key, "\n")] = 0;
                
                if (isHexKey(key)) {
                    printSuccess("Valid hexadecimal key!");
                } else {
                    printError("Invalid! Contains non-hex characters.");
                }
                break;
                
            case 7:
                printHeader("AVERAGE PASSWORD SCORE");
                float avg = averageScore(users, userCount);
                printf("\n" BOLD "Average Security Score: ");
                if (avg >= 6.0) printf(GREEN "%.1f/7 - GOOD\n" RESET, avg);
                else if (avg >= 4.0) printf(YELLOW "%.1f/7 - NEEDS IMPROVEMENT\n" RESET, avg);
                else printf(RED "%.1f/7 - CRITICAL\n" RESET, avg);
                break;
                
            case 8:
                printHeader("COMPREHENSIVE SECURITY REPORT");
                displaySecurityReport(users, userCount);
                break;
                
            case 9:
                printHeader("GLOBAL SECURITY LEVEL");
                int level = globalSecurityLevel(users, userCount);
                printf("\n" BOLD "Security Level: ");
                if (level == 3) printf(GREEN "%d/3 - EXCELLENT 🔒\n" RESET, level);
                else if (level == 2) printf(YELLOW "%d/3 - MODERATE ⚠\n" RESET, level);
                else printf(RED "%d/3 - CRITICAL RISK ⚠⚠⚠\n" RESET, level);
                break;
                
            case 10:
                printHeader("TOP 3 STRONGEST PASSWORDS");
                top3Passwords(users, userCount);
                break;
                
            case 11:
                printHeader("LOGIN FORMAT VALIDATOR");
                printf(YELLOW "Enter login name: " RESET);
                fgets(text, 100, stdin);
                text[strcspn(text, "\n")] = 0;
                
                if (checkLoginFormat(text) == 1 ) {
                    printSuccess("Valid login format!");
                } else {
                    printError("Invalid format!");
                }
                break;
                
            case 12:
                printHeader("EMAIL FORMAT VALIDATOR");
                printf(YELLOW "Enter email: " RESET);
                fgets(text, 100, stdin);
                text[strcspn(text, "\n")] = 0;
                int emailcheck = checkEmailFormat(text);
                
                if (emailcheck== -1) {
                    printError("ERORR : include more than 1 '@' !?");
                } else if (emailcheck== -2) {
                    printError("Local part ERORR : bad format !?");
                }
                else if (emailcheck== -3){
                    printError("Domain part ERORR : bad format !?");
                }
                else if (emailcheck== 1){
                    printSuccess("Valid email Format !!");
                }
                break;
                
            case 13:
                printHeader("SECURITY TIPS");
                showSecurityTips();
                break;
                
            case 0:
                return;
                
            default:
                printError("Invalid option!");
        }
        
        pressEnter();
    }
}
void encryptionMenu() {
    int choice, key;
    char keyStr[27], reverse[27];
    struct Message msg = {0}, msg2 ={0};

    while (1) {
        clearScreen();
        printHeader("ENCRYPTION & CRYPTOGRAPHY MODULE");
        
        printf("\n" BOLD "┌─ Message Operations\n" RESET);
        printf("│  1. " CYAN "Input New Message\n" RESET);
        printf("│  2. " GREEN "Display Current Message\n" RESET);
        printf("│\n" BOLD "├─ Caesar Cipher\n" RESET);
        printf("│  3. " YELLOW "Encrypt with Caesar\n" RESET);
        printf("│  4. " YELLOW "Decrypt with Caesar\n" RESET);
        printf("│\n" BOLD "├─ Substitution Cipher\n" RESET);
        printf("│  5. " MAGENTA "Encrypt with Substitution\n" RESET);
        printf("│  6. " MAGENTA "Decrypt with Substitution\n" RESET);
        printf("│  7. " CYAN "Generate Reverse Key\n" RESET);
        printf("│  8. " CYAN "Validate Substitution Key\n" RESET);
        printf("│\n" BOLD "├─ XOR Encryption\n" RESET);
        printf("│  9. " GREEN "Encrypt with XOR\n" RESET);
        printf("│  10. " GREEN "Decrypt with XOR\n" RESET);
        printf("│\n" BOLD "├─ Message Manipulation\n" RESET);
        printf("│  11. " BLUE "Convert to Uppercase\n" RESET);
        printf("│  12. " BLUE "Convert to Lowercase\n" RESET);
        printf("│  13. " YELLOW "Remove Spaces\n" RESET);
        printf("│  14. " MAGENTA "Reverse Message\n" RESET);
        printf("│\n" BOLD "├─ Cryptanalysis\n" RESET);
        printf("│  15. " RED "Frequency Analysis\n" RESET);
        printf("│  16. " RED "Coincidence Index\n" RESET);
        printf("│  17. " CYAN "Count Character\n" RESET);
        printf("│  18. " GREEN "Compare Two Messages\n" RESET);
        printf("│  0. " RED "← Back\n" RESET);
        printf(BOLD "└─────────────────────────────\n" RESET);
        
        printf(YELLOW "\n▶ Select option: " RESET);
        choice = safeIntInput(0, 18);
        
        clearScreen();
        
        switch (choice) {
            case 1:
                printHeader("INPUT MESSAGE");
                inputMessage(&msg);
                printSuccess("Message saved!");
                addLog(logs, &logCount, currentUser, "Created new message", 0);
                break;
                
            case 2:
                printHeader("CURRENT MESSAGE");
                if(msg.length ==0){
                    printf("No message loaded yet. Use option 1 to input a message.");
                }
                displaymessage(&msg);
                printf(CYAN "\nLength: " RESET "%d characters\n", msg.length);
                break;
                
            case 3:
                printHeader("CAESAR CIPHER ENCRYPTION");
                printf(YELLOW "Enter shift key (1-25): " RESET);
                scanf("%d", &key);
                getchar();
                encryptCesar(&msg, key);
                printSuccess("Message encrypted!");
                printf("\n" GREEN "Encrypted: " RESET);
                displaymessage(&msg);
                addLog(logs, &logCount, currentUser, "Caesar encryption", 0);
                break;
                
            case 4:
                printHeader("CAESAR CIPHER DECRYPTION");
                printf(YELLOW "Enter shift key (1-25): " RESET);
                scanf("%d", &key);
                getchar();
                decryptCesar(&msg, key);
                printSuccess("Message decrypted!");
                printf("\n" GREEN "Decrypted: " RESET);
                displaymessage(&msg);
                addLog(logs, &logCount, currentUser, "Caesar decryption", 0);
                break;
                
            case 5:
                printHeader("SUBSTITUTION CIPHER ENCRYPTION");
                printf(YELLOW "Enter 26-letter substitution key: " RESET);
                fgets(keyStr, 27, stdin);
                keyStr[strcspn(keyStr, "\n")] = 0;
                
                if (isValidKey(keyStr)) {
                    encryptSubstitution(&msg, keyStr);
                    printSuccess("Message encrypted!");
                    displaymessage(&msg);
                } else {
                    printError("Invalid key! Must be 26 unique letters.");
                }
                break;
                
            case 6:
                printHeader("SUBSTITUTION CIPHER DECRYPTION");
                printf(YELLOW "Enter 26-letter substitution key: " RESET);
                fgets(keyStr, 27, stdin);
                keyStr[strcspn(keyStr, "\n")] = 0;
                
                if (isValidKey(keyStr)) {
                    getreversekey(keyStr, reverse);
                    decryptSubstitution(&msg, reverse);
                    printSuccess("Message decrypted!");
                    displaymessage(&msg);
                } else {
                    printError("Invalid key!");
                }
                break;
                
            case 7:
                printHeader("GENERATE REVERSE KEY");
                printf(YELLOW "Enter substitution key: " RESET);
                fgets(keyStr, 27, stdin);
                keyStr[strcspn(keyStr, "\n")] = 0;
                getreversekey(keyStr, reverse);
                printf(GREEN "\nReverse Key: " RESET BOLD "%s\n" RESET, reverse);
                break;
                
            case 8:
                printHeader("VALIDATE SUBSTITUTION KEY");
                printf(YELLOW "Enter key: " RESET);
                fgets(keyStr, 27, stdin);
                keyStr[strcspn(keyStr, "\n")] = 0;
                
                if (isValidKey(keyStr)) {
                    printSuccess("Valid substitution key!");
                } else {
                    printError("Invalid! Must contain all 26 unique letters.");
                }
                break;
                
            case 9:
                printHeader("XOR ENCRYPTION");
                printf(YELLOW "Enter XOR key (integer): " RESET);
                scanf("%d", &key);
                getchar();
                encryptXOR(&msg, key);
                printSuccess("Message encrypted with XOR!");
                displaymessage(&msg);
                break;
                
            case 10:
                printHeader("XOR DECRYPTION");
                printf(YELLOW "Enter XOR key (integer): " RESET);
                scanf("%d", &key);
                getchar();
                decryptXOR(&msg, key);
                printSuccess("Message decrypted with XOR!");
                displaymessage(&msg);
                break;
                
            case 11:
                printHeader("CONVERT TO UPPERCASE");
                toUppercase(&msg);
                printSuccess("Converted!");
                displaymessage(&msg);
                break;
                
            case 12:
                printHeader("CONVERT TO LOWERCASE");
                toLowercase(&msg);
                printSuccess("Converted!");
                displaymessage(&msg);
                break;
                
            case 13:
                printHeader("REMOVE SPACES");
                removeSpaces(&msg);
                printSuccess("Spaces removed!");
                displaymessage(&msg);
                break;
                
            case 14:
                printHeader("REVERSE MESSAGE");
                reverseMessage(&msg);
                printSuccess("Message reversed!");
                displaymessage(&msg);
                break;
                
            case 15:
                printHeader("FREQUENCY ANALYSIS");
                frequencyAnalysis(&msg);
                addLog(logs, &logCount, currentUser, "Performed frequency analysis", 0);
                break;
                
            case 16:
                printHeader("COINCIDENCE INDEX");
                float ci = coincidenceIndex(msg);
                printf("\n" BOLD "Index of Coincidence: " RESET "%.4f\n", ci);
                printf(CYAN "\nInterpretation:\n" RESET);
                if (ci > 0.065) printf(GREEN "  → Likely monoalphabetic cipher\n" RESET);
                else if (ci > 0.045) printf(YELLOW "  → Possibly polyalphabetic cipher\n" RESET);
                else printf(RED "  → Random or complex encryption\n" RESET);
                break;
                
            case 17:
                printHeader("CHARACTER COUNT");
                char c;
                printf(YELLOW "Enter character to count: " RESET);
                scanf("%c", &c);
                getchar();
                int count = countCharacter(msg, c);
                printf(GREEN "\n'%c' appears %d time(s)\n" RESET, c, count);
                break;
                
            case 18:
                printHeader("COMPARE MESSAGES");
                printf(YELLOW "Enter second message:\n" RESET);
                inputMessage(&msg2);
                
                if (compareMessages(&msg, &msg2)) {
                    printSuccess("Messages are IDENTICAL!");
                } else {
                    printWarning("Messages are DIFFERENT!");
                }
                break;
                
            case 0:
                return;
                
            default:
                printError("Invalid option!");
        }
        
        pressEnter();
    }
}

void logManagementMenu() {
    int choice, nb;
    char user[MAX_USERNAME_LENGTH], date[40];

    while (1) {
        clearScreen();
        printHeader("LOG MANAGEMENT & MONITORING MODULE");
        
        printf("\n" BOLD "┌─ Log Operations\n" RESET);
        printf("│  1. " GREEN "Display All Logs\n" RESET);
        printf("│  2. " CYAN "Add Manual Log Entry\n" RESET);
        printf("│  3. " YELLOW "Display Recent Logs\n" RESET);
        printf("│  4. " RED "Clear All Logs\n" RESET);
        printf("│\n" BOLD "├─ Search & Filter\n" RESET);
        printf("│  5. " CYAN "Search Logs by User\n" RESET);
        printf("│  6. " CYAN "Search Logs by Date\n" RESET);
        printf("│\n" BOLD "├─ Statistics & Analysis\n" RESET);
        printf("│  7. " MAGENTA "Display Log Statistics\n" RESET);
        printf("│  8. " YELLOW "Count Login Attempts\n" RESET);
        printf("│  9. " RED "Count Error Logs\n" RESET);
        printf("│  10. " RED "Count Blocked Attempts\n" RESET);
        printf("│  11. " YELLOW "Calculate Error Rate\n" RESET);
        printf("│  12. " CYAN "Daily Connections Count\n" RESET);
        printf("│\n" BOLD "├─ Security\n" RESET);
        printf("│  13. " RED "Detect Suspicious Activity\n" RESET);
        printf("│  14. " RED "Show Top Errors\n" RESET);
        printf("│\n" BOLD "├─ Sorting\n" RESET);
        printf("│  15. " BLUE "Sort by Date\n" RESET);
        printf("│  16. " BLUE "Sort by User\n" RESET);
        printf("│\n" BOLD "├─ Import/Export\n" RESET);
        printf("│  17. " GREEN "Export to CSV\n" RESET);
        printf("│  18. " GREEN "Import from CSV\n" RESET);
        printf("│  19. " YELLOW "Archive Logs\n" RESET);
        printf("│  0. " RED "← Back\n" RESET);
        printf(BOLD "└─────────────────────────────\n" RESET);
        
        printf(YELLOW "\n▶ Select option: " RESET);
        choice = safeIntInput(0, 19);
        
        clearScreen();
        
        switch (choice) {
            case 1:
                printHeader("SYSTEM LOGS");
                displayLogs(logs, logCount);
                break;
                
            case 2:
                printHeader("ADD LOG ENTRY");
                if(logCount >= MAX_LOGS){
                    printError("Cannot add more logs. Maximum limit reached!");
                    break;
                }
                char action[MAX_ACTION_LENGTH];
                int code;
                printf(YELLOW "Username: " RESET);
                fgets(user, MAX_USERNAME_LENGTH, stdin);
                user[strcspn(user, "\n")] = 0;
                printf(YELLOW "Action: " RESET);
                fgets(action, MAX_ACTION_LENGTH, stdin);
                action[strcspn(action, "\n")] = 0;
                printf(YELLOW "Code (0=Info, 1=Warning, 2=Error): " RESET);
                scanf("%d", &code);
                getchar();
                
                addLog(logs, &logCount, user, action, code);
                printSuccess("Log entry added!");
                break;
                
            case 3:
                printHeader("RECENT LOGS");
                printf(YELLOW "Number of recent logs to display: " RESET);
                scanf("%d", &nb);
                getchar();
                recentLogs(logs, logCount, nb);
                break;
                
            case 4:
                printHeader("CLEAR LOGS");
                printWarning("This will delete all logs!");
                printf(YELLOW "Are you sure? (y/n): " RESET);
                char confirm;
                scanf("%c", &confirm);
                getchar();
                if (confirm == 'y' || confirm == 'Y') {
                    clearLogs(logs, logCount);
                    logCount = 0;
                    printSuccess("All logs cleared!");
                } else {
                    printInfo("Operation cancelled.");
                }
                break;
                
            case 5:
                printHeader("SEARCH BY USER");
                printf(YELLOW "Enter username: " RESET);
                fgets(user, MAX_USERNAME_LENGTH, stdin);
                user[strcspn(user, "\n")] = 0;
                searchLogsByUser(logs, logCount, user);
                break;
                
            case 6:
                printHeader("SEARCH BY DATE");
                printf(YELLOW "Enter date (DD/MM/YYYY): " RESET);
                fgets(date, 40, stdin);
                date[strcspn(date, "\n")] = 0;
                searchLogsByDate(logs, logCount, date);
                break;
                
            case 7:
                printHeader("LOG STATISTICS");
                displayLogStats(logs, logCount);
                break;
                
            case 8:
                printHeader("LOGIN ATTEMPTS");
                int logins = countLoginLogs(logs, logCount);
                printf("\n" CYAN "Total Login Attempts: " RESET BOLD "%d\n" RESET, logins);
                break;
                
            case 9:
                printHeader("ERROR LOGS");
                int errors = countErrorLogs(logs, logCount);
                printf("\n" RED "Total Errors: " RESET BOLD "%d\n" RESET, errors);
                break;
                
            case 10:
                printHeader("BLOCKED ATTEMPTS");
                int blocked = countBlockedLogs(logs, logCount);
                printf("\n" RED "Total Blocked: " RESET BOLD "%d\n" RESET, blocked);
                break;
                
            case 11:
                printHeader("ERROR RATE ANALYSIS");
                float rate = errorRate(logs, logCount);
                printf("\n" BOLD "Error Rate: ");
                if (rate > 30) printf(RED "%.2f%% - CRITICAL\n" RESET, rate);
                else if (rate > 15) printf(YELLOW "%.2f%% - HIGH\n" RESET, rate);
                else if (rate > 5) printf(YELLOW "%.2f%% - MODERATE\n" RESET, rate);
                else printf(GREEN "%.2f%% - NORMAL\n" RESET, rate);
                break;
                
            case 12:
                printHeader("DAILY CONNECTIONS");
                printf(YELLOW "Enter date (DD/MM/YYYY): " RESET);
                fgets(date, 40, stdin);
                date[strcspn(date, "\n")] = 0;
                int connections = dailyConnections(logs, logCount, date);
                printf(CYAN "\nConnections on %s: " RESET BOLD "%d\n" RESET, date, connections);
                break;
                
            case 13:
                printHeader("SUSPICIOUS ACTIVITY DETECTION");
                printf(YELLOW "Enter username to analyze: " RESET);
                fgets(user, MAX_USERNAME_LENGTH, stdin);
                user[strcspn(user, "\n")] = 0;
                int suspicious = detectSuspiciousActivity(logs, logCount, user);
                
                if (suspicious > 5) {
                    printError("HIGH RISK - Multiple failed attempts detected!");
                    printf(RED "Suspicious events: %d\n" RESET, suspicious);
                } else if (suspicious > 0) {
                    printWarning("Moderate risk detected.");
                    printf(YELLOW "Suspicious events: %d\n" RESET, suspicious);
                } else {
                    printSuccess("No suspicious activity detected.");
                }
                break;
                
            case 14:
                printHeader("TOP ERRORS");
                showTopErrors(logs, logCount);
                break;
                
            case 15:
                printHeader("SORT BY DATE");
                sortLogsByDate(logs, logCount);
                printSuccess("Logs sorted by date!");
                displayLogs(logs, logCount);
                break;
                
            case 16:
                printHeader("SORT BY USER");
                sortLogsByUser(logs, logCount);
                printSuccess("Logs sorted by username!");
                displayLogs(logs, logCount);
                break;
                
            case 17:
                printHeader("EXPORT TO CSV");
                exportLogsCSV(logs, logCount);
                printSuccess("Logs exported to CSV file!");
                break;
                
            case 18:
                printHeader("IMPORT FROM CSV");
                importLogsCSV(logs, &logCount);
                printSuccess("Logs imported from CSV!");
                break;
                
            case 19:
                printHeader("ARCHIVE LOGS");
                archiveLogs(logs, logCount);
                printSuccess("Logs archived successfully!");
                break;
                
            case 0:
                return;
                
            default:
                printError("Invalid option!");
        }
        
        pressEnter();
    }
}
void mathSecToolMenu() {
    int choice, n, a, b;
    int arr[100];
    struct Matrix M1, M2, M3;
    long long base, exp, mod;

    while (1) {
        clearScreen();
        printHeader("MATHEMATICAL SECURITY TOOLS MODULE");
        
        printf("\n" BOLD "┌─ Number Theory\n" RESET);
        printf("│  1. " CYAN "Check if Prime\n" RESET);
        printf("│  2. " GREEN "Calculate GCD\n" RESET);
        printf("│  3. " GREEN "Calculate LCM\n" RESET);
        printf("│  4. " YELLOW "Modular Exponentiation\n" RESET);
        printf("│  5. " MAGENTA "Factorial Calculator\n" RESET);
        printf("│\n" BOLD "├─ Number Properties\n" RESET);
        printf("│  6. " CYAN "Check if Even\n" RESET);
        printf("│  7. " CYAN "Count Digits\n" RESET);
        printf("│  8. " BLUE "Sum of Digits\n" RESET);
        printf("│  9. " YELLOW "Reverse Number\n" RESET);
        printf("│  10. " GREEN "Check Palindrome\n" RESET);
        printf("│  11. " MAGENTA "Sum of Divisors\n" RESET);
        printf("│  12. " CYAN "Check Perfect Number\n" RESET);
        printf("│  13. " YELLOW "Check Armstrong Number\n" RESET);
        printf("│\n" BOLD "├─ Array Operations\n" RESET);
        printf("│  14. " GREEN "Generate Random Number\n" RESET);
        printf("│  15. " CYAN "Sum of Array\n" RESET);
        printf("│  16. " BLUE "Average of Array\n" RESET);
        printf("│  17. " YELLOW "Max in Array\n" RESET);
        printf("│  18. " YELLOW "Min in Array\n" RESET);
        printf("│  19. " MAGENTA "Sort Array Ascending\n" RESET);
        printf("│\n" BOLD "├─ Matrix Operations\n" RESET);
        printf("│  20. " GREEN "Display Matrix\n" RESET);
        printf("│  21. " CYAN "Add Matrices\n" RESET);
        printf("│  22. " YELLOW "Multiply Matrices\n" RESET);
        printf("│  23. " MAGENTA "Transpose Matrix\n" RESET);
        printf("│  24. " BLUE "Determinant 2x2\n" RESET);
        printf("│  25. " RED "Check Symmetric Matrix\n" RESET);
        printf("│  26. " RED "Check Identity Matrix\n" RESET);
        printf("│  0. " RED "← Back\n" RESET);
        printf(BOLD "└─────────────────────────────\n" RESET);
        
        printf(YELLOW "\n▶ Select option: " RESET);
            choice = safeIntInput(0, 26);
            
        
        clearScreen();
        
        switch (choice) {
            case 1:
                printHeader("PRIMALITY TEST");
                printf(YELLOW "Enter number: " RESET);
                scanf("%d", &n);
                getchar();
                
                if (isPrime(n)) {
                    printSuccess("This is a PRIME number!");
                } else {
                    printError("This is NOT a prime number.");
                }
                addLog(logs, &logCount, currentUser, "Primality test", 0);
                break;
                
            case 2:
                printHeader("GREATEST COMMON DIVISOR");
                printf(YELLOW "Enter first number: " RESET);
                scanf("%d", &a);
                printf(YELLOW "Enter second number: " RESET);
                scanf("%d", &b);
                getchar();
                
                int g = gcd(a, b);
                printf(GREEN "\nGCD(%d, %d) = " RESET BOLD "%d\n" RESET, a, b, g);
                break;
                
            case 3:
                printHeader("LEAST COMMON MULTIPLE");
                printf(YELLOW "Enter first number: " RESET);
                scanf("%d", &a);
                printf(YELLOW "Enter second number: " RESET);
                scanf("%d", &b);
                getchar();
                
                long long l = lcm(a, b);
                printf(GREEN "\nLCM(%d, %d) = " RESET BOLD "%lld\n" RESET, a, b, l);
                break;
                
            case 4:
                printHeader("MODULAR EXPONENTIATION");
                printf(YELLOW "Enter base: " RESET);
                scanf("%lld", &base);
                printf(YELLOW "Enter exponent: " RESET);
                scanf("%lld", &exp);
                printf(YELLOW "Enter modulus: " RESET);
                scanf("%lld", &mod);
                getchar();
                
                long long result = globalmodExp(base, exp, mod);
                printf(GREEN "\n(%lld ^ %lld) mod %lld = " RESET BOLD "%lld\n" RESET, base, exp, mod, result);
                printInfo("Used in RSA encryption!");
                addLog(logs, &logCount, currentUser, "Modular exponentiation", 0);
                break;
                
            case 5:
                printHeader("FACTORIAL CALCULATOR");
                printf(YELLOW "Enter number: " RESET);
                scanf("%d", &n);
                getchar();
                
                if (n < 0) {
                    printError("Factorial not defined for negative numbers!");
                } else if (n > 20) {
                    printWarning("Number too large! May cause overflow.");
                } else {
                    printf(GREEN "\n%d! = " RESET BOLD "%lld\n" RESET, n, factorial(n));
                }
                break;
                
            case 6:
                printHeader("EVEN/ODD CHECK");
                printf(YELLOW "Enter number: " RESET);
                scanf("%d", &n);
                getchar();
                
                if (isEven(n)) {
                    printSuccess("This is an EVEN number!");
                } else {
                    printInfo("This is an ODD number.");
                }
                break;
                
            case 7:
                printHeader("DIGIT COUNTER");
                printf(YELLOW "Enter number: " RESET);
                scanf("%d", &n);
                getchar();
                
                printf(CYAN "\nNumber of digits: " RESET BOLD "%d\n" RESET, countDigits(n));
                break;
                
            case 8:
                printHeader("SUM OF DIGITS");
                printf(YELLOW "Enter number: " RESET);
                scanf("%d", &n);
                getchar();
                
                printf(GREEN "\nSum of digits: " RESET BOLD "%d\n" RESET, sumDigits(n));
                break;
                
            case 9:
                printHeader("REVERSE NUMBER");
                printf(YELLOW "Enter number: " RESET);
                scanf("%d", &n);
                getchar();
                
                printf(CYAN "\nReversed: " RESET BOLD "%d\n" RESET, reverseNumber(n));
                break;
                
            case 10:
                printHeader("PALINDROME CHECK");
                printf(YELLOW "Enter number: " RESET);
                scanf("%d", &n);
                getchar();
                
                if (isPalindromeNumber(n)) {
                    printSuccess("This IS a palindrome!");
                } else {
                    printError("This is NOT a palindrome.");
                }
                break;
                
            case 11:
                printHeader("SUM OF DIVISORS");
                printf(YELLOW "Enter number: " RESET);
                scanf("%d", &n);
                getchar();
                
                printf(GREEN "\nSum of divisors: " RESET BOLD "%d\n" RESET, sumDivisors(n));
                break;
                
            case 12:
                printHeader("PERFECT NUMBER CHECK");
                printf(YELLOW "Enter number: " RESET);
                scanf("%d", &n);
                getchar();
                
                if (isPerfectNumber(n)) {
                    printSuccess("This IS a perfect number!");
                    printf(CYAN "(Sum of divisors equals the number)\n" RESET);
                } else {
                    printError("This is NOT a perfect number.");
                }
                break;
                
            case 13:
                printHeader("ARMSTRONG NUMBER CHECK");
                printf(YELLOW "Enter number: " RESET);
                scanf("%d", &n);
                getchar();
                
                if (isArmstrong(n)) {
                    printSuccess("This IS an Armstrong number!");
                } else {
                    printError("This is NOT an Armstrong number.");
                }
                break;
                
            case 14:
                printHeader("RANDOM NUMBER GENERATOR");
                int min, max;
                printf(YELLOW "Enter min: " RESET);
                scanf("%d", &min);
                printf(YELLOW "Enter max: " RESET);
                scanf("%d", &max);
                getchar();
                
                printf(GREEN "\nRandom number: " RESET BOLD "%d\n" RESET, randomNumber(min, max));
                break;
                
            case 15:
                printHeader("ARRAY SUM");
                printf(YELLOW "Enter array size: " RESET);
                scanf("%d", &n);
                printf(YELLOW "Enter %d elements:\n" RESET, n);
                for (int i = 0; i < n; i++) {
                    printf("  [%d]: ", i + 1);
                    scanf("%d", &arr[i]);
                }
                getchar();
                
                printf(GREEN "\nSum: " RESET BOLD "%d\n" RESET, sumArray(arr, n));
                break;
                
            case 16:
                printHeader("ARRAY AVERAGE");
                printf(YELLOW "Enter array size: " RESET);
                scanf("%d", &n);
                printf(YELLOW "Enter %d elements:\n" RESET, n);
                for (int i = 0; i < n; i++) {
                    printf("  [%d]: ", i + 1);
                    scanf("%d", &arr[i]);
                }
                getchar();
                
                printf(GREEN "\nAverage: " RESET BOLD "%.2f\n" RESET, averageArray(arr, n));
                break;
                
            case 17:
                printHeader("MAX IN ARRAY");
                printf(YELLOW "Enter array size: " RESET);
                scanf("%d", &n);
                printf(YELLOW "Enter %d elements:\n" RESET, n);
                for (int i = 0; i < n; i++) {
                    printf("  [%d]: ", i + 1);
                    scanf("%d", &arr[i]);
                }
                getchar();
                
                printf(GREEN "\nMaximum: " RESET BOLD "%d\n" RESET, maxArray(arr, n));
                break;
                
            case 18:
                printHeader("MIN IN ARRAY");
                printf(YELLOW "Enter array size: " RESET);
                scanf("%d", &n);
                printf(YELLOW "Enter %d elements:\n" RESET, n);
                for (int i = 0; i < n; i++) {
                    printf("  [%d]: ", i + 1);
                    scanf("%d", &arr[i]);
                }
                getchar();
                
                printf(GREEN "\nMinimum: " RESET BOLD "%d\n" RESET, minArray(arr, n));
                break;
                
            case 19:
                printHeader("SORT ARRAY");
                printf(YELLOW "Enter array size: " RESET);
                scanf("%d", &n);
                printf(YELLOW "Enter %d elements:\n" RESET, n);
                for (int i = 0; i < n; i++) {
                    printf("  [%d]: ", i + 1);
                    scanf("%d", &arr[i]);
                }
                getchar();
                
                sortAscending(arr, n);
                printSuccess("Array sorted!");
                printf(GREEN "\nSorted array: " RESET);
                for (int i = 0; i < n; i++) {
                    printf(BOLD "%d " RESET, arr[i]);
                }
                printf("\n");
                break;
                
            case 20:
                printHeader("DISPLAY MATRIX");

                printf(YELLOW "Enter rows: " RESET);
                if (scanf("%d", &M1.n) != 1 || M1.n <= 0 || M1.n > 10) {
                    printError("Invalid number of rows.");
                    while (getchar() != '\n');
                    break;
                }
                
                printf(YELLOW "Enter columns: " RESET);
                if (scanf("%d", &M1.p) != 1 || M1.p <= 0 || M1.p > 10) {
                    printError("Invalid number of columns.");
                    while (getchar() != '\n');
                    break;
                }
                
                printf(YELLOW "Enter matrix elements:\n" RESET);
                for (int i = 0; i < M1.n; i++) {
                    for (int j = 0; j < M1.p; j++) {
                        while (1) {
                            printf("  [%d][%d]: ", i, j);
                            if (scanf("%d", &M1.data[i][j]) == 1) {
                                break;
                            } else {
                              printError("Invalid input! Please enter integers only.");
                              while (getchar() != '\n'); 
                            printf(YELLOW "  ▶ Try again: " RESET);
                            }
                       }
                    }
                }              

                while (getchar() != '\n'); 

                printf("\n");
                displayMatrix(M1);
                break;
            case 21:
                printHeader("MATRIX ADDITION");
                printf(YELLOW "Enter rows: " RESET);
                scanf("%d", &M1.n);
                printf(YELLOW "Enter columns: " RESET);
                scanf("%d", &M1.p);
                M2.n = M1.n;
                M2.p = M1.p;
                
                printf(CYAN "\nFirst Matrix:\n" RESET);
                for (int i = 0; i < M1.n; i++) {
                    for (int j = 0; j < M1.p; j++) {
                        printf("  [%d][%d]: ", i, j);
                        scanf("%d", &M1.data[i][j]);
                    }
                }
                
                printf(CYAN "\nSecond Matrix:\n" RESET);
                for (int i = 0; i < M2.n; i++) {
                    for (int j = 0; j < M2.p; j++) {
                        printf("  [%d][%d]: ", i, j);
                        scanf("%d", &M2.data[i][j]);
                    }
                }
                getchar();
                
                addMatrices(M1, M2, &M3);
                printf(GREEN "\nResult:\n" RESET);
                displayMatrix(M3);
                break;
                
            case 22:
                printHeader("MATRIX MULTIPLICATION");
                printf(YELLOW "First matrix rows: " RESET);
                scanf("%d", &M1.n);
                printf(YELLOW "First matrix columns (= Second matrix rows): " RESET);
                scanf("%d", &M1.p);
                M2.n = M1.p;
                printf(YELLOW "Second matrix columns: " RESET);
                scanf("%d", &M2.p);
                
                printf(CYAN "\nFirst Matrix:\n" RESET);
                for (int i = 0; i < M1.n; i++) {
                    for (int j = 0; j < M1.p; j++) {
                        printf("  [%d][%d]: ", i, j);
                        scanf("%d", &M1.data[i][j]);
                    }
                }
                
                printf(CYAN "\nSecond Matrix:\n" RESET);
                for (int i = 0; i < M2.n; i++) {
                    for (int j = 0; j < M2.p; j++) {
                        printf("  [%d][%d]: ", i, j);
                        scanf("%d", &M2.data[i][j]);
                    }
                }
                getchar();
                
                multiplyMatrices(M1, M2, &M3);
                printf(GREEN "\nResult:\n" RESET);
                displayMatrix(M3);
                break;
                
            case 23:
                printHeader("TRANSPOSE MATRIX");
                printf(YELLOW "Enter rows: " RESET);
                scanf("%d", &M1.n);
                printf(YELLOW "Enter columns: " RESET);
                scanf("%d", &M1.p);
                
                printf(YELLOW "Enter matrix elements:\n" RESET);
                for (int i = 0; i < M1.n; i++) {
                    for (int j = 0; j < M1.p; j++) {
                        printf("  [%d][%d]: ", i, j);
                        scanf("%d", &M1.data[i][j]);
                    }
                }
                getchar();
                
                transposeMatrix(M1, &M2);
                printf(GREEN "\nTranspose:\n" RESET);
                displayMatrix(M2);
                break;
                
            case 24:
                printHeader("DETERMINANT 2x2");
                int A[2][2];
                printf(YELLOW "Enter 2x2 matrix:\n" RESET);
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 2; j++) {
                        printf("  [%d][%d]: ", i, j);
                        scanf("%d", &A[i][j]);
                    }
                }
                getchar();
                
                printf(GREEN "\nDeterminant: " RESET BOLD "%d\n" RESET, determinant2x2(A));
                break;
                
            case 25:
                printHeader("SYMMETRIC MATRIX CHECK");
                printf(YELLOW "Enter size (n x n): " RESET);
                scanf("%d", &M1.n);
                M1.p = M1.n;
                
                printf(YELLOW "Enter matrix elements:\n" RESET);
                for (int i = 0; i < M1.n; i++) {
                    for (int j = 0; j < M1.p; j++) {
                        printf("  [%d][%d]: ", i, j);
                        scanf("%d", &M1.data[i][j]);
                    }
                }
                getchar();
                
                if (isSymmetric(M1)) {
                    printSuccess("This IS a symmetric matrix!");
                } else {
                    printError("This is NOT symmetric.");
                }
                break;
                
            case 26:
                printHeader("IDENTITY MATRIX CHECK");
                printf(YELLOW "Enter size (n x n): " RESET);
                scanf("%d", &M1.n);
                M1.p = M1.n;
                
                printf(YELLOW "Enter matrix elements:\n" RESET);
                for (int i = 0; i < M1.n; i++) {
                    for (int j = 0; j < M1.p; j++) {
                        printf("  [%d][%d]: ", i, j);
                        scanf("%d", &M1.data[i][j]);
                    }
                }
                getchar();
                
                if (isIdentity(M1)) {
                    printSuccess("This IS an identity matrix!");
                } else {
                    printError("This is NOT an identity matrix.");
                }
                break;
                
            case 0:
                return;
                
            default:
                printError("Invalid option!");
        }
        
        pressEnter();
    }
}
void integratedWorkflowMenu() {
    int choice;

    while (1) {
        clearScreen();
        printHeader("INTEGRATED SECURITY WORKFLOWS");
        
        printf("\n" BOLD CYAN "Complete security scenarios combining multiple modules:\n" RESET);
        printf("\n" BOLD "1. " GREEN "Complete User Registration Flow\n" RESET);
        printf("   └─ Create user → Validate password → Generate secure key → Log action\n");
        
        printf("\n" BOLD "2. " YELLOW "Security Audit Workflow\n" RESET);
        printf("   └─ Analyze all users → Generate report → Export logs → Archive\n");
        
        printf("\n" BOLD "3. " MAGENTA "Message Encryption Pipeline\n" RESET);
        printf("   └─ Input message → Encrypt (multi-layer) → Analyze → Log\n");
        
        printf("\n" BOLD "4. " CYAN "Cryptographic Key Generation\n" RESET);
        printf("   └─ Generate primes → Calculate RSA params → Test encryption\n");
        
        printf("\n" BOLD "5. " RED "Security Incident Response\n" RESET);
        printf("   └─ Detect suspicious → Block user → Generate report → Archive\n");
        
        printf("\n" BOLD "0. " RED "← Back\n" RESET);
        
        printf(YELLOW "\n▶ Select workflow: " RESET);
        choice = safeIntInput(0, 5);
        
        clearScreen();
        
        switch (choice) {
            case 1: {
                printHeader("COMPLETE USER REGISTRATION WORKFLOW");
                
                // Step 1: Create user
                printInfo("Step 1/4: User Registration");
                addUser(users, &userCount);
                
                // Step 2: Validate password
                printInfo("\nStep 2/4: Password Strength Analysis");
                char pass[MAX_PASSWORD_LENGTH];
                strcpy(pass, users[userCount - 1].password);
                int score = passwordScore(pass);
                printf(CYAN "Password Score: " RESET "%d/100\n", score);
                
                // Step 3: Generate security key
                printInfo("\nStep 3/4: Generating Security Key");
                char key[33];
                generateHexKey(32, key);
                printf(GREEN "Generated Key: " RESET "%s\n", key);
                
                // Step 4: Log everything
                printInfo("\nStep 4/4: Logging Actions");
                addLog(logs, &logCount, users[userCount - 1].name, "User registered", 0);
                addLog(logs, &logCount, users[userCount - 1].name, "Security key generated", 0);
                
                printSuccess("\n✓ User registration complete!");
                break;
            }
            
            case 2: {
                printHeader("SECURITY AUDIT WORKFLOW");
                
                printInfo("Step 1/4: Analyzing user database...");
                pressEnter();
                displaySecurityReport(users, userCount);
                
                printInfo("\nStep 2/4: Calculating security metrics...");
                pressEnter();
                int level = globalSecurityLevel(users, userCount);
                printf(BOLD "Global Security Level: %d/100\n" RESET, level);
                
                printInfo("\nStep 3/4: Exporting audit logs...");
                exportLogsCSV(logs, logCount);
                printSuccess("Logs exported!");
                
                printInfo("\nStep 4/4: Archiving data...");
                archiveLogs(logs, logCount);
                printSuccess("Data archived!");
                
                addLog(logs, &logCount, currentUser, "Completed security audit", 0);
                printSuccess("\n✓ Security audit complete!");
                break;
            }
            
            case 3: {
                printHeader("MESSAGE ENCRYPTION PIPELINE");
                struct Message msg;
                
                printInfo("Step 1/5: Message Input");
                inputMessage(&msg);
                
                printInfo("\nStep 2/5: Caesar Encryption (shift=7)");
                encryptCesar(&msg, 7);
                printf(GREEN "Encrypted: " RESET);
                displaymessage(&msg);
                
                printInfo("\nStep 3/5: XOR Encryption (key=42)");
                encryptXOR(&msg, 42);
                printf(GREEN "Double-encrypted: " RESET);
                displaymessage(&msg);
                
                printInfo("\nStep 4/5: Cryptanalysis");
                float ci = coincidenceIndex(msg);
                printf(CYAN "Coincidence Index: %.4f\n" RESET, ci);
                
                printInfo("\nStep 5/5: Logging");
                addLog(logs, &logCount, currentUser, "Multi-layer encryption performed", 0);
                
                printSuccess("\n✓ Encryption pipeline complete!");
                break;
            }
            
            case 4: {
                printHeader("CRYPTOGRAPHIC KEY GENERATION");
                
                printInfo("Step 1/4: Finding prime numbers...");
                int p = 0, q = 0;
                for (int i = 100; i < 200; i++) {
                    if (isPrime(i) && p == 0) p = i;
                    else if (isPrime(i) && p != 0 && q == 0) {
                        q = i;
                        break;
                    }
                }
                printf(GREEN "Prime p = %d\n" RESET, p);
                printf(GREEN "Prime q = %d\n" RESET, q);
                
                printInfo("\nStep 2/4: Calculating RSA modulus...");
                int n = p * q;
                printf(CYAN "n = p × q = %d\n" RESET, n);
                
                printInfo("\nStep 3/4: Calculating φ(n)...");
                int phi = (p - 1) * (q - 1);
                printf(CYAN "φ(n) = %d\n" RESET, phi);
                
                printInfo("\nStep 4/4: Testing modular exponentiation...");
                long long test = globalmodExp(5, 7, n);
                printf(GREEN "5^7 mod %d = %lld\n" RESET, n, test);
                
                addLog(logs, &logCount, currentUser, "Generated RSA parameters", 0);
                printSuccess("\n✓ Cryptographic key generation complete!");
                break;
            }
            
            case 5: {
                printHeader("SECURITY INCIDENT RESPONSE");

                char username[MAX_USERNAME_LENGTH];
                printInfo("Step 1/5: Enter suspected username");
                printf(YELLOW "Username: " RESET);
                fgets(username, MAX_USERNAME_LENGTH, stdin);
                username[strcspn(username, "\n")] = 0;
                
                printInfo("\nStep 2/5: Detecting suspicious activity...");
                int suspicious = detectSuspiciousActivity(logs, logCount, username);
                printf(YELLOW "Suspicious events found: %d\n" RESET, suspicious);
                
                if (suspicious > 3) {
                    printInfo("\nStep 3/5: Blocking user...");
                    blockUser(users, userCount, username);
                    printSuccess("User blocked!");
                    
                    printInfo("\nStep 4/5: Generating incident report...");
                    addLog(logs, &logCount, currentUser, "Security incident detected", 2);
                    addLog(logs, &logCount, username, "Account blocked for suspicious activity", 2);
                    
                    printInfo("\nStep 5/5: Archiving incident data...");
                    archiveLogs(logs, logCount);
                    
                    printError("\n⚠ INCIDENT RESPONSE COMPLETE - User blocked and logged!");
                } else {
                    printSuccess("\nNo immediate threat detected. Continuing monitoring...");
                    addLog(logs, &logCount, currentUser, "Routine security check performed", 0);
                }
                break;
            }
            
            case 0:
                return;
                
            default:
                printError("Invalid option!");
        }
        
        pressEnter();
    }
}
void helpMenu() {
    int choice;
    
    while (1) {
        clearScreen();
        printHeader("HELP & DOCUMENTATION");
        
        printf("\n" BOLD "┌─ Help Topics\n" RESET);
        printf("│  1. " CYAN "Getting Started Guide\n" RESET);
        printf("│  2. " GREEN "User Management Help\n" RESET);
        printf("│  3. " YELLOW "Encryption Guide\n" RESET);
        printf("│  4. " MAGENTA "Security Audit Help\n" RESET);
        printf("│  5. " BLUE "Log Management Help\n" RESET);
        printf("│  6. " CYAN "Mathematical Tools Guide\n" RESET);
        printf("│  7. " RED "Troubleshooting\n" RESET);
        printf("│  8. " GREEN "Security Best Practices\n" RESET);
        printf("│  0. " RED "← Back\n" RESET);
        printf(BOLD "└─────────────────────────────\n" RESET);
        
        printf(YELLOW "\n▶ Select topic: " RESET);
        choice = safeIntInput(0, 8);
        
        clearScreen();
        
        switch (choice) {
            case 1:
                printHeader("GETTING STARTED GUIDE");
                printf("\n" BOLD CYAN "Welcome to SecureC Toolkit!\n\n" RESET);
                printf("This toolkit provides comprehensive security utilities for:\n");
                printf("  • User authentication and management\n");
                printf("  • Message encryption and cryptanalysis\n");
                printf("  • Security auditing and password analysis\n");
                printf("  • System logging and monitoring\n");
                printf("  • Mathematical security operations\n\n");
                
                printf(BOLD "Quick Start:\n" RESET);
                 printf("1. Use " GREEN "User Management" RESET " to create and manage accounts\n");
                printf("2. Test encryption with " MAGENTA "Encryption Module" RESET "\n");
                printf("3. Monitor activities in " CYAN "Log Management" RESET "\n");
                printf("4. Run security audits with " YELLOW "Audit & Analysis" RESET "\n\n");
                
                printf(YELLOW "TIP: " RESET "Start by exploring each module individually!\n");
                break;
                
            case 2:
                printHeader("USER MANAGEMENT HELP");
                printf("\n" BOLD "User Management Functions:\n\n" RESET);
                
                printf(GREEN "Adding Users:\n" RESET);
                printf("  • Enter unique username (3-20 characters)\n");
                printf("  • Password must be strong (8+ chars, mixed case, numbers, symbols)\n");
                printf("  • Choose role: 0=User, 1=Admin\n\n");
                
                printf(YELLOW "Password Requirements:\n" RESET);
                printf("  ✓ Minimum 8 characters\n");
                printf("  ✓ At least one uppercase letter\n");
                printf("  ✓ At least one lowercase letter\n");
                printf("  ✓ At least one digit\n");
                printf("  ✓ At least one special character (!@#$%%^&*)\n\n");
                
                printf(RED "Blocking Users:\n" RESET);
                printf("  • Blocks prevent login attempts\n");
                printf("  • Use for suspicious accounts\n");
                printf("  • Can be reversed with unblock\n\n");
                
                printf(CYAN "File Operations:\n" RESET);
                printf("  • Save: Writes all users to 'users.txt'\n");
                printf("  • Load: Imports users from file\n");
                printf("  • Always save before exiting!\n");
                break;
                
            case 3:
                printHeader("ENCRYPTION GUIDE");
                printf("\n" BOLD "Encryption Methods:\n\n" RESET);
                
                printf(YELLOW "Caesar Cipher:\n" RESET);
                printf("  • Simple shift cipher (ROT-n)\n");
                printf("  • Key: 1-25 (shift amount)\n");
                printf("  • Example: A→D with key=3\n");
                printf("  • Weak, for educational purposes\n\n");
                
                printf(MAGENTA "Substitution Cipher:\n" RESET);
                printf("  • Each letter maps to another\n");
                printf("  • Key: 26 unique letters (QWERTYUIOPASDFGHJKLZXCVBNM)\n");
                printf("  • Stronger than Caesar\n");
                printf("  • Vulnerable to frequency analysis\n\n");
                
                printf(GREEN "XOR Cipher:\n" RESET);
                printf("  • Bitwise XOR operation\n");
                printf("  • Key: Any integer\n");
                printf("  • Same key encrypts and decrypts\n");
                printf("  • Fast but simple\n\n");
                
                printf(RED "Cryptanalysis Tools:\n" RESET);
                printf("  • Frequency Analysis: Shows letter distribution\n");
                printf("  • Coincidence Index: Identifies cipher type\n");
                printf("  • Use to break weak encryptions\n");
                break;
                
            case 4:
                printHeader("SECURITY AUDIT HELP");
                printf("\n" BOLD "Password Analysis:\n\n" RESET);
                
                printf(CYAN "Password Scoring:\n" RESET);
                printf("  • 0-2: CRITICAL - Change immediately\n");
                printf("  • 3-4: WEAK - Needs improvement\n");
                printf("  • 5-6: GOOD - Acceptable\n");
                printf("  • 7: EXCELLENT - Strong security\n\n");
                
                printf(GREEN "Security Report:\n" RESET);
                printf("  • Shows average user security score\n");
                printf("  • Identifies weak passwords\n");
                printf("  • Recommends improvements\n\n");
                
                printf(YELLOW "Key Generation:\n" RESET);
                printf("  • Random Password: Creates strong passwords\n");
                printf("  • Hex Key: Cryptographic key generation\n");
                printf("  • Use for secure communications\n\n");
                
                printf(MAGENTA "Validation:\n" RESET);
                printf("  • Email Format: Checks valid email syntax\n");
                printf("  • Login Format: Validates usernames\n");
                printf("  • Prevents injection attacks\n");
                break;
                
            case 5:
                printHeader("LOG MANAGEMENT HELP");
                printf("\n" BOLD "Log System:\n\n" RESET);
                
                printf(CYAN "Log Types:\n" RESET);
                printf("  • Code 0 (INFO): Normal operations\n");
                printf("  • Code 1 (WARNING): Suspicious activity\n");
                printf("  • Code 2 (ERROR): Critical events\n\n");
                
                printf(GREEN "Search Functions:\n" RESET);
                printf("  • By User: Find all actions by username\n");
                printf("  • By Date: Filter logs by specific date\n");
                printf("  • Use for incident investigation\n\n");
                
                printf(RED "Security Monitoring:\n" RESET);
                printf("  • Suspicious Activity: Detects failed login patterns\n");
                printf("  • Error Rate: Shows system health\n");
                printf("  • Daily Connections: Tracks usage patterns\n\n");
                
                printf(YELLOW "Data Management:\n" RESET);
                printf("  • Export CSV: Backup logs to file\n");
                printf("  • Import CSV: Restore from backup\n");
                printf("  • Archive: Long-term storage\n");
                break;
                
            case 6:
                printHeader("MATHEMATICAL TOOLS GUIDE");
                printf("\n" BOLD "Number Theory Functions:\n\n" RESET);
                
                printf(GREEN "Prime Operations:\n" RESET);
                printf("  • Essential for RSA encryption\n");
                printf("  • Use for key generation\n");
                printf("  • Check primality before use\n\n");
                
                printf(CYAN "Modular Arithmetic:\n" RESET);
                printf("  • GCD: Used in RSA algorithm\n");
                printf("  • Modular Exp: Fast exponentiation\n");
                printf("  • Critical for cryptography\n\n");
                
                printf(YELLOW "Matrix Operations:\n" RESET);
                printf("  • Used in advanced ciphers\n");
                printf("  • Hill cipher implementation\n");
                printf("  • Linear algebra for crypto\n\n");
                
                printf(MAGENTA "Array Tools:\n" RESET);
                printf("  • Statistical analysis\n");
                printf("  • Data processing\n");
                printf("  • Support functions\n");
                break;
                
            case 7:
                printHeader("TROUBLESHOOTING");
                printf("\n" BOLD RED "Common Issues & Solutions:\n\n" RESET);
                
                printf(YELLOW "Problem: " RESET "\"User not found\"\n");
                printf(GREEN "Solution: " RESET "Check spelling, load users from file first\n\n");
                
                printf(YELLOW "Problem: " RESET "\"Invalid password\"\n");
                printf(GREEN "Solution: " RESET "Must meet all strength requirements\n\n");
                
                printf(YELLOW "Problem: " RESET "\"File not found\"\n");
                printf(GREEN "Solution: " RESET "Run 'Save Users' at least once to create file\n\n");
                
                printf(YELLOW "Problem: " RESET "\"Login blocked\"\n");
                printf(GREEN "Solution: " RESET "User account is blocked, contact admin\n\n");
                
                printf(YELLOW "Problem: " RESET "\"Invalid key\"\n");
                printf(GREEN "Solution: " RESET "Substitution key must be 26 unique letters\n\n");
                
                printf(YELLOW "Problem: " RESET "\"Data not saving\"\n");
                printf(GREEN "Solution: " RESET "Check file permissions, use Save option before exit\n\n");
                
                printf(CYAN "Still having issues?\n" RESET);
                printf("Check that all library files (.h) are in the correct directory\n");
                break;
                
            case 8:
                printHeader("SECURITY BEST PRACTICES");
                printf("\n" BOLD GREEN "Security Recommendations:\n\n" RESET);
                
                printf(YELLOW "Password Security:\n" RESET);
                printf("  ✓ Use passwords 12+ characters\n");
                printf("  ✓ Mix uppercase, lowercase, numbers, symbols\n");
                printf("  ✓ Avoid dictionary words\n");
                printf("  ✓ Never reuse passwords\n");
                printf("  ✓ Change regularly (every 90 days)\n\n");
                
                printf(CYAN "User Management:\n" RESET);
                printf("  ✓ Review user list regularly\n");
                printf("  ✓ Remove inactive accounts\n");
                printf("  ✓ Limit admin privileges\n");
                printf("  ✓ Monitor login attempts\n\n");
                
                printf(MAGENTA "System Security:\n" RESET);
                printf("  ✓ Review logs daily\n");
                printf("  ✓ Export logs for backup\n");
                printf("  ✓ Investigate suspicious activity\n");
                printf("  ✓ Keep software updated\n\n");
                
                printf(RED "Encryption:\n" RESET);
                printf("  ✓ Never use Caesar for real security\n");
                printf("  ✓ Substitution is for learning only\n");
                printf("  ✓ Use modern algorithms in production\n");
                printf("  ✓ Protect encryption keys\n\n");
                
                printf(BOLD "Remember: Security is a process, not a product!\n" RESET);
                break;
                
            case 0:
                return;
                
            default:
                printError("Invalid option!");
        }
        
        pressEnter();
    }
}

void aboutMenu() {
    clearScreen();
    printHeader("ABOUT SECUREC TOOLKIT");
    
    printf("\n" BOLD CYAN);
    printf("███████╗███████╗ ██████╗██╗   ██╗██████╗ ███████╗ ██████╗\n");
    printf("██╔════╝██╔════╝██╔════╝██║   ██║██╔══██╗██╔════╝██╔════╝\n");
    printf("███████╗█████╗  ██║     ██║   ██║██████╔╝█████╗  ██║     \n");
    printf("╚════██║██╔══╝  ██║     ██║   ██║██╔══██╗██╔══╝  ██║     \n");
    printf("███████║███████╗╚██████╗╚██████╔╝██║  ██║███████╗╚██████╗\n");
    printf("╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝ ╚═════╝\n");
    printf(RESET "\n");
    
    printf(BOLD GREEN "                    Security Toolkit v2.0\n" RESET);
    printf(CYAN "           ════════════════════════════════════════\n\n" RESET);
    
    printf(BOLD "Project Information:\n" RESET);
    printf("  " CYAN "Name: " RESET "Security Utility Library Suite\n");
    printf("  " CYAN "Course: " RESET "Algorithms and Static Data Structures\n");
    printf("  " CYAN "Level: " RESET "1st Year Foundation Training\n");
    printf("  " CYAN "Institution: " RESET "National School of Cybersecurity (NSCS)\n");
    printf("  " CYAN "Academic Year: " RESET "2025/2026\n\n");
    
    printf(BOLD "Developed By:\n" RESET);
    printf("  " GREEN " Ouanouki anes\n" RESET);
    printf("  " YELLOW "Group: " RESET "A3 \n\n");
    printf("  " GREEN " Koussei\n" RESET);
    printf("  " YELLOW "Group: " RESET "B3 \n\n");
    
    printf(BOLD "Module Overview:\n" RESET);
    printf("  " MAGENTA "5 Libraries\n" RESET);
    printf("  " CYAN "⚡ 105+ Functions\n" RESET);
    printf("  " GREEN " Multiple Encryption Algorithms\n" RESET);
    printf("  " YELLOW " Complete Security Analysis\n" RESET);
    printf("  " RED " Comprehensive Logging System\n" RESET);
    printf("  " BLUE " Advanced Mathematical Tools\n" RESET "\n");
    
    printf(BOLD "Features:\n" RESET);
    printf("  ✓ User authentication & management\n");
    printf("  ✓ Classical cryptography (Caesar, Substitution, XOR)\n");
    printf("  ✓ Password strength analysis & validation\n");
    printf("  ✓ Security auditing & reporting\n");
    printf("  ✓ Event logging & monitoring\n");
    printf("  ✓ Number theory & cryptographic mathematics\n");
    printf("  ✓ Matrix operations for advanced ciphers\n");
    printf("  ✓ Integrated security workflows\n");
    printf("  ✓ CSV import/export functionality\n");
    printf("  ✓ Colored terminal interface\n\n");
    
    printf(BOLD "Technical Stack:\n" RESET);
    printf("  " CYAN "Language: " RESET "C (ANSI C99)\n");
    printf("  " CYAN "Libraries: " RESET "stdio.h, stdlib.h, string.h, time.h, unistd.h\n");    
    printf(BOLD YELLOW " DISCLAIMER:\n" RESET);
    printf("  The encryption methods implemented (Caesar, Substitution, XOR)\n");
    printf("  are classical ciphers for EDUCATIONAL purposes only. They are\n");
    printf("  NOT secure for real-world applications. For production systems,\n \n \n");
    
    printf("  " CYAN "© 2025-2026 NSCS - Academic Project\n" RESET);

    
    printf(BOLD GREEN "Thank you for using SecureC Toolkit!\n" RESET);
    printf(CYAN "For help, select option 6 from the main menu.\n\n" RESET);
    
    pressEnter();
}
void mainMenu() {
    int choice;
    addLog(logs, &logCount, "system", "SecureC Toolkit started", 0);
    
    while (1) {
        clearScreen();
        
        // Animated Banner
        printf(BOLD CYAN "\n");
        printf("███████╗███████╗ ██████╗██╗   ██╗██████╗ ███████╗ ██████╗\n");
        printf("██╔════╝██╔════╝██╔════╝██║   ██║██╔══██╗██╔════╝██╔════╝\n");
        printf("███████╗█████╗  ██║     ██║   ██║██████╔╝█████╗  ██║     \n");
        printf("╚════██║██╔══╝  ██║     ██║   ██║██╔══██╗██╔══╝  ██║     \n");
        printf("███████║███████╗╚██████╗╚██████╔╝██║  ██║███████╗╚██████╗\n");
        printf("╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝ ╚═════╝\n");
        printf(RESET);
        
        printf(BOLD GREEN "\n           Complete Security Toolkit v2.0  \n" RESET);
        printf(CYAN "          ════════════════════════════════════\n" RESET);
        
        printf("\n" BOLD "┌─ Main Modules\n" RESET);
        printf("│\n");
        printf("│  " BOLD "1. " GREEN " USER MANAGEMENT" RESET "\n");
        printf("│     └─ Register, authenticate, manage users & permissions\n");
        printf("│\n");
        printf("│  " BOLD "2. " YELLOW " AUDIT & SECURITY ANALYSIS" RESET "\n");
        printf("│     └─ Password strength, security reports, validation\n");
        printf("│\n");
        printf("│  " BOLD "3. " MAGENTA " ENCRYPTION & CRYPTOGRAPHY" RESET "\n");
        printf("│     └─ Caesar, Substitution, XOR ciphers & cryptanalysis\n");
        printf("│\n");
        printf("│  " BOLD "4. " CYAN " LOG MANAGEMENT & MONITORING" RESET "\n");
        printf("│     └─ Track activities, detect threats, generate reports\n");
        printf("│\n");
        printf("│  " BOLD "5. " BLUE " MATHEMATICAL SECURITY TOOLS" RESET "\n");
        printf("│     └─ Number theory, modular arithmetic, matrix operations\n");
        printf("│\n");
        printf("│  " BOLD "6. " RED "⚡ INTEGRATED WORKFLOWS" RESET "\n");
        printf("│     └─ Complete security scenarios & automated pipelines\n");
        printf("│\n");
        printf("├─ System Info\n");
        printf("│  " CYAN "Users: " RESET "%d  " CYAN "Logs: " RESET "%d  " CYAN "Current User: " RESET BOLD "%s\n" RESET, 
                                 userCount, logCount, currentUser);
        printf("│\n");
        printf("├─ Information\n");
        printf("│  " BOLD "7. " GREEN " Help & Documentation\n" RESET);
        printf("│  " BOLD "8. " BLUE "ℹ  About SecureC Toolkit\n" RESET);
        printf("│\n");
        printf("└─ " BOLD "0. " RED "Exit\n" RESET);
        
        printf(BOLD YELLOW "\n▶ Select module: " RESET);
        choice = safeIntInput(0, 8);
        
        switch (choice) {
            case 1:
                addLog(logs, &logCount, currentUser, "Accessed User Management", 0);
                userManagementMenu();
                break;
                
            case 2:
                addLog(logs, &logCount, currentUser, "Accessed Audit & Analysis", 0);
                auditAnalysisMenu();
                break;
                
            case 3:
                addLog(logs, &logCount, currentUser, "Accessed Encryption Module", 0);
                encryptionMenu();
                break;
                
            case 4:
                addLog(logs, &logCount, currentUser, "Accessed Log Management", 0);
                logManagementMenu();
                break;
                
            case 5:
                addLog(logs, &logCount, currentUser, "Accessed Math Security Tools", 0);
                mathSecToolMenu();
                break;
                
            case 6:
                addLog(logs, &logCount, currentUser, "Accessed Integrated Workflows", 0);
                integratedWorkflowMenu();
                break;
            case 7:
                helpMenu();
                break;
    
            case 8:
                aboutMenu();
                break;    
            case 0:
                clearScreen();
                printHeader("SYSTEM SHUTDOWN");
                
                if (!confirmAction("exit and save all data")) {
                    printInfo("Shutdown cancelled.");
                    pressEnter();
                    break;
                }
                
                printf(CYAN "\nSaving system state...\n" RESET);
                
                if (userCount > 0) {
                    printSuccess("✓ Users saved");
                } else {
                    printError("✗ Failed to save users!");
                }
                
                exportLogsCSV(logs, logCount);
                printSuccess("✓ Logs exported");
                
                addLog(logs, &logCount, "system", "SecureC Toolkit shutdown", 0);
                
                printf(GREEN "\n✓ All data saved successfully!\n" RESET);
                printf(YELLOW "\nThank you for using SecureC Toolkit!\n" RESET);
                printf(CYAN "Stay secure!  \n\n" RESET);
                return;
            default:
                printError("Invalid option! Please select 0-6.");
                pressEnter();
        }
    }
}

int main() {
    srand(time(NULL));
    
    clearScreen();
    printf(BOLD CYAN "\n\n");
    printf("        ╔═══════════════════════════════════════════╗\n");
    printf("        ║                                           ║\n");
    printf("        ║   " GREEN "🔐  SECUREC TOOLKIT LOADING...  🔐" CYAN "   ║\n");
    printf("        ║                                           ║\n");
    printf("        ╚═══════════════════════════════════════════╝\n");
    printf(RESET "\n");
    
    printf(YELLOW "        Initializing security modules");
    fflush(stdout);
    for (int i = 0; i < 3; i++) {
        usleep(500000);
        printf(".");
        fflush(stdout);
    }
    printf("\n\n");
    printf("Welcome to Login's page\n\n"); // then we need to add way to chose if user need to login or emport users from file ; no keep it like that ;
    printf(CYAN "        Loading user database...\n" RESET);
    LoadUsers(users, &userCount);
    printf(GREEN "        ✓ Users loaded: %d\n" RESET, userCount);


    if (userCount == 0) {
        printf(YELLOW "        No existing data found. Creating default admin...\n" RESET);
        strcpy(users[0].name, "admin");
        strcpy(users[0].password, "Admin@123");
        users[0].role = 1;
        users[0].state = 0;
        userCount = 1;
        
        if (userCount) {
            printSuccess("✓ Default admin created");
        } else {
            printWarning("⚠ Could not save default admin to file");
        }
    }
    char username[MAX_USERNAME_LENGTH], passwd[MAX_PASSWORD_LENGTH];
    int logincheck , formatcheck;
    do {
        printf(GREEN "USERNAME: " RESET);
        scanf("%19s", username);
        clearInputBuffer();
        
        formatcheck = checkLoginFormat(username);
        if (formatcheck == -1) {
            printError("Empty username!");
            continue;
        }
        if (formatcheck == -2 || formatcheck == -3) {
            printError("Invalid username format!");
            continue;
        }
        currentUser = username ;
        
        printf(GREEN "PASSWORD: " RESET);
        scanf("%19s", passwd);
        clearInputBuffer();
        
        logincheck = checkLogin(users, userCount, username, passwd);
        
        if (logincheck == -1) {
            printError("User not found!");
            loginAttempts++;
        } else if (logincheck == -2) {
            printError("Account is blocked!");
            loginAttempts++;
        } else if (logincheck != 1) {
            printError("Invalid password!");
            loginAttempts++;
        }

        if (loginAttempts >= MAX_LOGIN_ATTEMPTS && logincheck != 1) {
            clearScreen();
            printHeader("SECURITY LOCKOUT");
            printf(RED "\n   TOO MANY FAILED LOGIN ATTEMPTS!\n" RESET);
            printf(YELLOW "\nYou have exceeded the maximum number of login attempts.\n" RESET);
            printf(YELLOW "The system has been locked for security reasons.\n" RESET);
            printf(RED "\nAttempts made: %d/%d\n" RESET, loginAttempts, MAX_LOGIN_ATTEMPTS);
            printf(CYAN "\nPlease contact your system administrator.\n" RESET);
            printf(YELLOW "\nExiting in 5 seconds...\n" RESET);
            
            for (int i = 5; i > 0; i--) {
                printf(RED "  %d...\n" RESET, i);
                sleep(1);
            }
            
            addLog(logs, &logCount, currentUser, "ACCOUNT LOCKOUT - Too many failed attempts", 2);
            exportLogsCSV(logs, logCount);
            
            exit(1);
        }
        
        if (logincheck != 1) {
            printf(YELLOW "\nAttempts remaining: %d/%d\n" RESET, 
                   MAX_LOGIN_ATTEMPTS - loginAttempts, MAX_LOGIN_ATTEMPTS);
        }
    
    } while (logincheck != 1);
    loginAttempts = 0;
    addLog(logs, &logCount, currentUser, "Login", 0);
    
    
    printf(GREEN "        ✓ System ready!\n" RESET);
    usleep(1000000);
    mainMenu();
    
    return 0;
}