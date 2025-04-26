#include "vec.h"

#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
// #include <stddef.h>

#include "../diag/diag.h"

vec vcreate(void) {
    
    unsigned cap = 50;
    double* ptr = malloc( cap * sizeof(double) );
    unsigned len = 0;

    vec v = {ptr, len, cap};

    return v;
};

vec vwith_cap( unsigned cap ) {
    double* ptr = malloc( cap * sizeof(double) );
    unsigned len = 0;

    vec v = {ptr, len, cap};

    return v;
};

void vappend( vec* v, double x) {

    if ( v->len == v->cap ) { 
        v->cap *= 2;
        
        v->ptr = realloc(v->ptr, v->cap * sizeof(double) );
    }

    v->ptr[v->len] = x;
    v->len++;

    return;
};

void vdestroy( vec* v ) {
    free(v->ptr);
    v->ptr = NULL;
    v->len = 0;
    v->cap = 0;
};


void printvec( vec v, char* format, char* sep ) {

    for ( unsigned i = 0; i < v.len; i++)
    {
        printf(format, *(v.ptr + i));
        printf("%s", sep);
    }

    if (strchr(sep, '\n') == NULL) { printf("\n");}
};

void vvvappend( txyvec* vvv, vec3 v ) {
    vappend( &vvv->t, v.o[0] );
    vappend( &vvv->x, v.o[1] );
    vappend( &vvv->y, v.o[2] );
}

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

vec linspacee(double a, double b, int n) {
    double j;
    vec v = vwith_cap(n+1);
    
    for (unsigned i = 0; i < v.cap; i++)
    {
        j = (double)i / (v.cap-1);

        vappend(&v, a + (b-a)*j);
    } 

    return v;
}

vec logspacee(double a, double b, int n) {
    double j;
    vec v = vwith_cap(n+1);
    
    for (unsigned i = 0; i < v.cap; i++) {

        j = (double)i / (v.cap-1);

        vappend(&v, a * pow(b/a,j) );
    } 

    return v;
}

// typedef struct Gvec {
//     const void* ptr;
//     size_t len;
//     size_t cap;
//     const size_t elem_size;
// } Gvec;

#define DEFAULT_GV_CAPACITY 128
#define u8 unsigned char

bool gv_is_null( const Gvec* gv ) {
    if ( gv->ptr == NULL || gv->cap == 0 || gv->elem_size == 0 ) {return true;}
    return false;
}

Gvec gv_new ( size_t elem_size ) {
    if (elem_size == 0){ cricical("Can't initialize a general purpose vec with 0 sized elements");}

    void* ptr = malloc( DEFAULT_GV_CAPACITY  * elem_size );

    return (Gvec){ .ptr = ptr, .elem_size = elem_size, .len = 0, .cap = DEFAULT_GV_CAPACITY};
}

Gvec gv_with_cap( size_t elem_size, size_t cap ) {

    if (elem_size == 0) { cricical("Can't initialize a general purpose vec with 0 sized elements");}
    if (cap == 0)       { cricical("Can't initialize a 0 cap general purpose vec"); }

    double* ptr = malloc( cap * elem_size );

    return (Gvec){ .ptr = ptr, .cap = cap, .len = 0, .elem_size = elem_size};
}

void gv_push (Gvec* gv_to_push, const void* elem_to_push ) {

    if ( gv_to_push  == NULL    ) { cricical("Gv pointer was nullptr"); }
    if ( gv_is_null(gv_to_push) ) { cricical("Gv provided was uninitialized or freed"); }
    if ( elem_to_push == NULL   ) { cricical("Elem to push was nullptr"); }

    if ( gv_to_push->len == gv_to_push->cap ) { 
        gv_to_push->cap *= 2;
        
        gv_to_push->ptr = realloc(gv_to_push->ptr, gv_to_push->cap * gv_to_push->elem_size );
    }

    u8* temp_ptr    = gv_to_push->ptr;
    temp_ptr       += gv_to_push->len * gv_to_push->elem_size;

    memcpy(temp_ptr, elem_to_push, gv_to_push->elem_size);

    gv_to_push->len++;

    return;
}

void* gv_get_ref( Gvec* gv_to_index, size_t index ) {

    if ( gv_to_index  == NULL     ) { cricical("Gv pointer was nullptr"); }
    if ( gv_is_null(gv_to_index)  ) { cricical("Gv provided was uninitialized or freed"); }
    if ( index >= gv_to_index->len) { cricical("Tried to access element OOB"); }

    return gv_to_index->ptr + index;
}

void    gv_destroy  ( Gvec* gv_to_destroy ){

    if ( gv_to_destroy  == NULL    ) { cricical("Gv pointer was nullptr"); }
    if ( gv_is_null(gv_to_destroy) ) { cricical("Gv provided was uninitialized or already freed"); }

    free(gv_to_destroy->ptr);

    *gv_to_destroy = (Gvec){0};
}


// typedef struct Multvec {
//     void* ptr;
//     size_t elem_size;
//     size_t arrays_len;
//     size_t n_arrays;
//     size_t cap;
// } Multvec;

#define DEFAULT_MV_CAPACITY 32

bool mv_is_null( const Multvec* mv ) {
    if ( mv->ptr == NULL || mv->cap == 0 || mv->elem_size == 0 || mv->arrays_len == 0 ) {return true;}
    return false;
}

Multvec mv_new ( size_t elem_size, size_t n_arrays ) {

    if (elem_size == 0){ cricical("Can't initialize a multivec with 0 sized elements");}
    if (n_arrays == 0) { cricical("Can't initialize a 0 arrays multvec"); }

    void* ptr = malloc( DEFAULT_MV_CAPACITY * elem_size * n_arrays );

    return (Multvec){ 
        .ptr = ptr, 
        .elem_size = elem_size, 
        .arrays_len = 0, 
        .n_arrays = n_arrays, 
        .cap = DEFAULT_GV_CAPACITY
    };
}

Multvec     mv_with_cap( size_t elem_size, size_t n_arrays, size_t cap ) {
    if (elem_size == 0){ cricical("Can't initialize a multivec with 0 sized elements");}
    if (n_arrays == 0) { cricical("Can't initialize a 0 arrays multvec"); }
    if (cap == 0)      { cricical("Can't initialize a 0 cap multvec"); }

    double* ptr = malloc( cap * elem_size * n_arrays );

    return (Multvec){ 
        .ptr = ptr, 
        .elem_size = elem_size, 
        .arrays_len = 0, 
        .n_arrays = n_arrays, 
        .cap = cap
    };
};

// void        mv_push_one( const Multvec* mv_to_push, const void* elem_to_push, size_t array_to_push );

void mv_push_all( Multvec* mv_to_push, const Gvec* array_to_push ) {
    if ( mv_to_push  == NULL    ) { cricical("Mv pointer was nullptr"); }
    if ( mv_is_null(mv_to_push) ) { cricical("Mv provided was uninitialized or freed"); }
    if ( array_to_push == NULL  ) { cricical("Elem to push was nullptr"); }
    if ( gv_is_null(array_to_push)) { cricical("Elem to push was uninitialized or freed"); }
    if ( array_to_push->len < mv_to_push->n_arrays ) { cricical("Too few elements in array to push to mvarray")}


    if ( mv_to_push->len == mv_to_push->cap ) { 
        mv_to_push->cap *= 2;
        
        mv_to_push->ptr = realloc(mv_to_push->ptr, mv_to_push->cap * mv_to_push->elem_size );
    }

    u8* temp_ptr    = mv_to_push->ptr;
    temp_ptr       += mv_to_push->len * mv_to_push->elem_size;

    memcpy(temp_ptr, elem_to_push, mv_to_push->elem_size);

    mv_to_push->len++;

    return;
};

void*       mv_get_ref ( Multvec* mv_to_index, size_t array_to_index, size_t index_in_array);
Gvec        mv_get_vec ( Multvec* mv_to_index, size_t array_to_index );
Gvec        mv_get_slc ( Multvec* mv_to_index, size_t index_in_array ); // void**

void        mv_destroy ( Multvec* to_destroy );