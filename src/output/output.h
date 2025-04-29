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

/// @brief this fn counts the occurrences of sub in src
/// @param src string from which to search
/// @param sub substring to find
/// @return number of occurrences
size_t str_count_sub( char* src, char* sub );

size_t count_ne_percent( char* src );

int g_printf( char* fmt, void* content, size_t size );
int m_printf( char* fmt, void* content, size_t len, size_t size );


// {
//     FILE* file = fopen(name, "w");


// };



// char* turn_num_to_roman(int);

#endif //__OUTPUT_H__