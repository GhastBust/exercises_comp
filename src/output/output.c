#include <stdio.h>

#include "output/output.h"

static void* file = 0;
static int chapter = 0;
static int sub = 0;
static char subfmt = 0;

void delete_and_open() { 
    file = fopen("results.txt", "w"); 
}

char* turn_num_to_roman(int n) 
{
    /*
    I = 1
    V = 5
    X = 10
    L = 50
    */

   if (n >= 100) {exit(1);}
   
   char buffer[9];
   const int b_size = 9;
   int b_index = 0;

    char letters[2][2] = {
        {'I', 'V'}, 
        {'X', 'L'}
    };

    int digits[2] = {n/10, n%10};

    for (int i = 0; i < 2; i++) {

        if (digits[i] == 9) { 
            snprintf(
                buffer+b_index, 
                b_size-b_index, 
                "%c%c", 
                letters[i][0], letters[i+1][0]
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
    ) { exit(1); }
    if (file == 0) { delete_and_open(); }

    subfmt = sub_format ;

    char buffer[40];
    int buffersize = 40;
    
    chapter += 1;
    int size = snprintf(buffer, buffersize, "%d) %s\n", chapter, name); //* turn the chapter into string

    fwrite(buffer, sizeof(char), size, file);   //* write chapter into file
}

void next_sub(void)
{

}