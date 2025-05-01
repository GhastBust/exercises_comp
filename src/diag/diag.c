#include "diag.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


void info(char* info, ...) {
    va_list argptr;
    va_start(argptr, info);
        
    printf("\x1b[94m[+] ");
    vprintf (info, argptr);
    printf("\x1b[0m\n");

    va_end(argptr);
}

void warning(char* warning, ...) {
    va_list argptr;
    va_start(argptr, warning);

    printf("\x1b[38;5;220m[*] ");
    vprintf (warning, argptr);    
    printf("\x1b[0m\n");

    va_end(argptr);
}

void critical( char* error, ... ) {
    va_list argptr;
    va_start(argptr, error);

    printf("\x1b[91m[!] ");
    vprintf (error, argptr);
    printf("\x1b[0m\n");

    printf("Exiting...\n");
    
    va_end(argptr);
    exit(EXIT_FAILURE);
}