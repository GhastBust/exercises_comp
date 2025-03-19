#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void next_chapter(char*, char);
void next_sub(void);
FILE* delete_and_open(void);

void csv_open_write(char* name);
void csv_write(double n);
void csv_new_line(void);
void csv_close();




// {
//     FILE* file = fopen(name, "w");


// };



// char* turn_num_to_roman(int);

#endif //__OUTPUT_H__