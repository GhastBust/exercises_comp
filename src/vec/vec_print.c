#include "vec.h"

#include <math.h>
#include <stdio.h>

#include "../diag/diag.h"
#include "../output/output.h"

void printvec( vec v, char* format, char* sep ) {

    for ( unsigned i = 0; i < v.len; i++)
    {
        printf(format, *(v.ptr + i));
        printf("%s", sep);
    }

    if (strchr(sep, '\n') == NULL) { printf("\n");}
};

void  vvvprint( txyvec v, char* format, char* sep ) {

    int minn = fmin(v.t.len, v.x.len);
    minn = fmin(minn, v.y.len);

    if ( sep == NULL ) {
        for (int i = 0; i < minn; i++){ 
            printf(format, v.t.ptr[i], v.x.ptr[i], v.y.ptr[i]);
            printf("\n");
        }
        return;
    }

    for (int i = 0; i < minn; i++){

        printf(format, v.t.ptr[i]);
        printf("%s", sep);        
        printf(format, v.x.ptr[i]);
        printf("%s", sep);        
        printf(format, v.y.ptr[i]);
        printf("\n");
    }

    return;

};


Gvec print_array_fmt( char *fmt, size_t len ) {

    /*
     * for the function: 
     * 
     * original fmt = ...
     * apple orange %% data paper: %d
     * ^              ^            ^
     * back           fmt          fwrd
     * 
     * the search for the '%' char is done only form
     * fmt to fwrd, but the whole string (from back to fwrd)
     * is copied in the buffer, after the '%' has been found
     * the string gets copied, appending it with a '\0' char
     */

    Gvec  bbuffer = gv_with_cap(sizeof(char*), len+1);
    char*  buffer = calloc( strlen(fmt) +len +2, sizeof(char));

    char* current_buffer = buffer;
    char* fmt_fwrd = fmt;
    char* fmt_back = fmt;

    while( (fmt_fwrd = strchr(fmt, '%')) != NULL ) {

        //* if '%' char has been escaped
        if (fmt_fwrd[1] == '%') { 
            fmt_fwrd += 2; 
            fmt = fmt_fwrd;
            continue; 
        }

        //* found '%'
        size_t word_len = fmt_fwrd - fmt_back;

        memcpy(current_buffer, fmt_back, word_len);
        gv_push(&bbuffer, &current_buffer);

        //* must add the '\0' char
        current_buffer += word_len + 1; 

        //* go foward with the pointers
        fmt_back = fmt_fwrd;
        fmt_fwrd++;
        fmt = fmt_fwrd;
    }

    //* push last part of string
    gv_push(&bbuffer, &fmt_back);

    return bbuffer;
}

#define u8 unsigned char

int gv_printf_case_1( Gvec* gv, char* format ) {
    int n;
    u8* gv_ptr = gv->ptr;

    for ( int i = 0; i < gv->len; i++ ) {
        n += g_printf(format, gv_ptr + (i * gv->elem_size), gv->elem_size);
    }

    n += printf("\n");
    return n;
}

int gv_printf_case_n( Gvec* gv, char *fmt ) {

    int written_chars = 0;
    Gvec strings = print_array_fmt(fmt, gv->len);

    if ( gv->len + 1 != strings.len ) {critical("Len of vectors was wierdly set");}

    written_chars += printf( "%s", *(char**)gv_get_ref(&strings, 0) );

    for ( int i = 0; i < gv->len; i++ ) {
        written_chars += g_printf( 
            *(char**)gv_get_ref(&strings, i+1),
            gv_get_ref(gv, i),
            gv->elem_size
        );
    }
    
    free( *(u8**)gv_get_ref(&strings, 0) );
    gv_destroy(&strings);
    return written_chars;
}


int gv_printf(Gvec *gv, char *format)
{
    int char_written = 0;
    size_t n_esc = count_ne_percent(format);
    
    if (n_esc == 0) { critical("Symbol %% not found in format string"); }
    if (n_esc == 1) { return gv_printf_case_1(gv, format); }

    if (n_esc == gv->len) { return gv_printf_case_n(gv, format); }

    critical("Number of %% symbols not conforming, enter either 1 or %ld (vec len), %ld was given", gv->len, n_esc);
    return 1;
}

int gv_fprintf_case_1( Gvec* gv, FILE *file_stream, char* format ) {
    int n;
    u8* gv_ptr = gv->ptr;

    for ( int i = 0; i < gv->len; i++ ) {
        n += g_printf(format, gv_ptr + (i * gv->elem_size), gv->elem_size);
    }

    n += printf("\n");
    return n;
}

int gv_fprintf_case_n( Gvec* gv, FILE *file_stream, char *fmt ) {

    int written_chars = 0;
    Gvec strings = print_array_fmt(fmt, gv->len);

    if ( gv->len + 1 != strings.len ) {critical("Len of vectors was wierdly set");}

    written_chars += printf( "%s", *(char**)gv_get_ref(&strings, 0) );

    for ( int i = 0; i < gv->len; i++ ) {
        written_chars += g_printf( 
            *(char**)gv_get_ref(&strings, i+1),
            gv_get_ref(gv, i),
            gv->elem_size
        );
    }
    
    free( *(u8**)gv_get_ref(&strings, 0) );
    gv_destroy(&strings);
    return written_chars;
}

// int gv_fprintf( Gvec *gv_to_print, void *file_stream_p, char *format )
// {
//     if ( file_stream_p == NULL ) {critical("File stream pointer was nullptr");}

//     FILE* file_stream = (FILE*) file_stream_p;

//     int char_written = 0;
//     size_t n_esc = count_ne_percent(format);
    
//     if (n_esc == 0) { critical("Symbol %% not found in format string"); }
//     if (n_esc == 1) { return gv_fprintf_case_1(gv, file_stream, format); }

//     if (n_esc == gv->len) { return gv_fprintf_case_n(gv, file_stream, format); }

//     critical("Number of %% symbols not conforming, enter either 1 or %ld (vec len), %ld was given", gv->len, n_esc);
//     return 1;
// }