#ifndef CLOGGER_TEST_CLOGGER_H
#define CLOGGER_TEST_CLOGGER_H
#include <stdio.h>

static FILE* fptr;

typedef enum tag_MODE {
    DEBUG_ALL, // print all statements to console and .log file
    DEBUG_FILE, // print all statements to .log file only
    RELEASE_ALL, // print "error" and "warning" statements to console and .log file
    RELEASE_FILE // print "error" and "warning" statements to ./log file only
} MODE;

typedef struct tag_Log {
    void (*info)(char*);
    void (*warn)(char*);
    void (*error)(char*);
} Log;

int initializeLogger(Log*, MODE);

#endif //CLOGGER_TEST_CLOGGER_H
