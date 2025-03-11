#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "output.h"

void* file = 0;
static int chapter = 0;
static int sub = 0;
static char subfmt = 0;

void* delete_and_open(void) { 
    file = fopen("results.txt", "w"); 
    return file;
};

char* turn_num_to_roman(int n) {
    /*
    I = 1
    V = 5
    X = 10
    L = 50
    */

   if (n >= 1000) {exit(1);}
   
   char* buffer = calloc(40, sizeof(char));
   const int b_size = 40;
   int b_index = 0;

    char letters[3][2] = {
        {'C', 'D'},
        {'X', 'L'},
        {'I', 'V'}, 
    };

    const int MAX_DIGITS = 3;
    int   digits[] = {n/100, n%100/10, n%10};

    for (int i = 0; i < MAX_DIGITS; i++) {

        if (digits[i] == 9) { 
            snprintf(
                buffer+b_index, 
                b_size-b_index, 
                "%c%c", 
                letters[i][0], letters[i-1][0]
            );
            b_index += 2;
            continue;
        };
        
        if (digits[i] == 4) {
            snprintf(
                buffer+b_index, 
                b_size-b_index, 
                "%c%c",
                letters[i][0], letters[i][1]
            );
            b_index += 2;
            continue;
        }

        if (digits[i] / 5 == 1)
        {
            snprintf(
                buffer+b_index, 
                b_size-b_index, 
                "%c",
                letters[i][1]
            );
            b_index += 1;
        }

        for (int j = 0; j < digits[i] % 5; j++)
        {
            snprintf(
                buffer+b_index, 
                b_size-b_index, 
                "%c",
                letters[i][0]
            );
            b_index += 1;
        }
    }
    
    return buffer;
}

void next_chapter(char* name, char sub_format)
{
    if (
        sub_format != '1' &&
        sub_format != 'a' && 
        sub_format != 'i' &&
        sub_format != 'I' 
    ) { 
        printf("[!] Unknown subchapter format, was: %c", sub_format);
        exit(1); 
    }


    if (!file) { delete_and_open(); }

    sub = 0;
    subfmt = sub_format ;

    const int BUFFERSIZE = 100;
    char buffer[BUFFERSIZE];
    
    chapter += 1;
    int size = snprintf(buffer, BUFFERSIZE, "\n%d) %s", chapter, name); //* turn the chapter into string

    fwrite(buffer, sizeof(char), size, file);   //* write chapter into file
}

void next_sub(void)
{
    const int BUFFERSIZE = 40;
    char buffer[BUFFERSIZE];

    char* index_str;
    sub += 1;

    switch (subfmt)
    {
    case 'I':
        index_str = turn_num_to_roman(sub);
        break;

    case 'i':
        index_str = turn_num_to_roman(sub);

        for (int i = 0; *(index_str+i) != '\0'; i++) 
        { *(index_str+i) += 32; } //* turn into lowercase
        break;

    case '1':
        const int DIGITS =  (int)log10(sub) +1;
        const char numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
        int single_digit;
        index_str = calloc( DIGITS + 1, sizeof(char));
        
        for (int i = 0; i < DIGITS ; i++ ) {
            single_digit = sub / (int)pow(10, DIGITS-i-1) % (int)pow(10, i);
            *(index_str + i) = numbers[single_digit];
        }

        break;

    case 'a':
        index_str = calloc( 2, sizeof(char) );
        *index_str = 96+sub;
        break;
    
    default:
        exit(EXIT_FAILURE);
        break;
    }
    
    int size = snprintf(buffer, BUFFERSIZE, "\n  %s) ", index_str); //* turn the chapter into string

    fwrite(buffer, sizeof(char), size, file);   //* write chapter into file
}