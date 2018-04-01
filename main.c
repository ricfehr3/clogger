#include <stdio.h>
#include "clogger.h"

int main() {
    Log log;
    if(initializeLogger(&log, DEBUG_ALL) == 0)
    {
        printf("clogger initialized\n");
    } else {
        printf("Error, clogger could not initialize\n");
    }

    log.info("This is for debug info");
    log.warn("This is for warnings");
    log.error("This is for errors");
}