#ifndef __VEC_H__
#define __VEC_H__

#include <stddef.h>

#include "../matr/matr.h"

typedef struct vec
{
    double* ptr;
    unsigned len;
    unsigned cap;
} vec;


// multvec muv_with_cap( unsigned cap );

vec     vcreate(void);
vec     vwith_cap( unsigned cap );
void    vappend( vec* v, double x );
void    vdestroy( vec* v);
void    printvec( vec v, char* format, char* sep );

vec linspacee(double a, double b, int n);
vec logspacee(double a, double b, int n);


typedef struct txyvec {
    vec t;
    vec x;
    vec y;
} txyvec;


void    vvvappend( txyvec* vvv, vec3 v );
void    vvvprint( txyvec v, char* format, char* sep );


typedef struct Gvec {
    void* ptr;
    size_t len;
    size_t cap;
    size_t elem_size;
} Gvec;

Gvec    gv_new      ( size_t elem_size );
Gvec    gv_with_cap ( size_t elem_size, size_t cap );

void    gv_push     ( Gvec* gv_to_push, const void* elem_to_push );
void*   gv_get_ref  ( Gvec* gv_to_index, size_t index );

void    gv_destroy  ( Gvec* gv_to_destroy );


typedef struct Multvec {
    void* ptr;
    size_t elem_size;
    size_t arrays_len;
    size_t n_arrays;
    size_t cap;
} Multvec;

Multvec     mv_new     ( size_t elem_size, size_t n_arrays ); 
Multvec     mv_with_cap( size_t elem_size, size_t n_arrays, size_t cap );

// void        mv_push_one( const Multvec* mv_to_push, const void* elem_to_push, size_t array_to_push );
void        mv_push_all( Multvec* mv_to_push, Gvec* array_to_push );
void*       mv_get_ref ( Multvec* mv_to_index, size_t array_to_index, size_t index_in_array);
Gvec        mv_get_vec ( Multvec* mv_to_index, size_t array_to_index );
Gvec        mv_get_slc ( Multvec* mv_to_index, size_t index_in_array ); // void**

void        mv_destroy ( Multvec* to_destroy );

#endif //__VEC_H__