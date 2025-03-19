#include <stdio.h>
#include <stdlib.h>
#include "diag.h"

void info(char* info) {
    printf("\x1b[94m[+] %s\x1b[0m\n", info);
}

void warning(char* warning) {
    printf("\x1b[38;5;220m[*] %s\x1b[0m\n", warning);
}

void cricical(char* error) {
    printf("\x1b[91m[!] %s\x1b[0m\n", error);
    printf("Exiting...\n");
    exit(EXIT_FAILURE);
}