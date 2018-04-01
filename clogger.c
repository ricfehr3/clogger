#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "include/clogger.h"

/*
 * This process_string function should not have any memory leaks.
 * The functions who call them do so recursively, so when the newStr is created it will be destroyed
 * at the end of it's scope. The newStr is returned and the pointer now points to the new str.
 * At least I hope...
 */
char* process_string(char* str) {
    char* newStr = malloc(strlen(str)+1);
    strcpy(newStr, str);
    strcat(newStr, "\n");
    return newStr;
}

static MODE mode;

// gets current time for logger, returns string in HH:MM:SS format
char* getCurrentTime() {
    time_t mytime;
    struct tm* timeinfo;

    time(&mytime);
    timeinfo = localtime(&mytime);
    return strtok(asctime(timeinfo), "\n");
}

// print info to STDOUT
void info(char* str, ...) {
    str = process_string(str);
    fprintf(fptr, "%s\t[INFO]: %s", getCurrentTime(), str);
    if (mode == DEBUG_ALL || mode == RELEASE_ALL) {
        printf("%s\t[INFO]: %s", getCurrentTime(), str);
    }
}

void debug(char* str, ...) {
    str = process_string(str);
    if((mode == DEBUG_ALL) || (mode == DEBUG_FILE)) {
        fprintf(fptr, "%s\t[DEBUG]: %s", getCurrentTime(), str);
        if (mode == DEBUG_ALL) {
            printf("%s\t[DEBUG]: %s", getCurrentTime(), str);
        }
    }
}

void warn(char* str, ...) {
    str = process_string(str);
    fprintf(fptr, "%s\t[WARNING]: %s", getCurrentTime(), str);
    if((mode == DEBUG_ALL) || (mode == RELEASE_ALL)) {
        printf("\e[1;36m"); // cyan
        printf("%s\t[WARNING]: %s", getCurrentTime(), str);
        printf("\e[0m"); // normal
    }
}

void error(char* str, ...) {
    str = process_string(str);
    fprintf(fptr, "%s\t[ERROR]: %s", getCurrentTime(), str);
    if((mode == DEBUG_ALL) || (mode == RELEASE_ALL)) {
        printf("\e[1;31m"); // red
        printf("%s\t[ERROR]: %s", getCurrentTime(), str);
        printf("\e[0m"); // normal
    }
}

int initializeLogger(Log* log, MODE initmode) {
    mode = initmode;

#ifdef __linux__
    // get current working directory
    char cwd[1024];
    char logstr[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        strcpy(logstr, cwd);
        strcat(logstr, "/run.log");
    } else {
        printf("Error, couldn't get current working directory\n");
        return -1;
    }
    // open file
    fptr = fopen(logstr, "w+");

    // Print Header
    fprintf(fptr, "%s at %s:\n", __DATE__, __TIME__);

    // point to correct functions
    log->info = info;
    log->debug = debug;
    log->warn = warn;
    log->error = error;

    return 0;
#elif __WIN32
    //TODO, this!!! Get cwd and open file
    printf("Error, windows is not implemented\n");
#else

#endif
}

// TODO: make variable number of arguments for info, warn, and error