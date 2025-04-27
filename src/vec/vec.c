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

Gvec gv_new ( size_t s ) {
    if (s == 0){ critical("Can't initialize a general purpose vec with 0 sized elements");}

    void* ptr = malloc( DEFAULT_GV_CAPACITY  * s );

    return (Gvec){ 
        .ptr = ptr, 
        .elem_size = s, 
        .len = 0, 
        .cap = DEFAULT_GV_CAPACITY
    };
}

Gvec gv_with_cap( size_t s, size_t cap ) {

    if (s == 0)   { critical("Can't initialize a general purpose vec with 0 sized elements");}
    if (cap == 0) { critical("Can't initialize a 0 cap general purpose vec"); }

    double* ptr = malloc( cap * s );

    return (Gvec){ 
        .ptr = ptr, 
        .cap = cap, 
        .len = 0, 
        .elem_size = s
    };
}

void gv_push (Gvec* gv, const void* elem ) {

    if ( gv  == NULL    ) { critical("Gv pointer was nullptr"); }
    if ( gv_is_null(gv) ) { critical("Gv provided was uninitialized or freed"); }
    if ( elem == NULL   ) { critical("Elem to push was nullptr"); }

    if ( gv->len == gv->cap ) { 
        gv->cap *= 2;
        
        gv->ptr = realloc(gv->ptr, gv->cap * gv->elem_size );
    }

    u8* temp_ptr    = gv->ptr;
    temp_ptr       += gv->len * gv->elem_size;

    memcpy(temp_ptr, elem, gv->elem_size);

    gv->len++;

    return;
}

void* gv_get_ref( Gvec* gv, size_t i ) {

    if ( gv  == NULL     ) { critical("Gv pointer was nullptr"); }
    if ( gv_is_null(gv)  ) { critical("Gv provided was uninitialized or freed"); }
    if ( i >= gv->len)     { critical("Tried to access element OOB"); }

    return (u8*)(gv->ptr) + i * gv->elem_size;
}

void    gv_destroy  ( Gvec* gv ){

    if ( gv  == NULL    ) { critical("Gv pointer was nullptr"); }
    if ( gv_is_null(gv) ) { critical("Gv provided was uninitialized or already freed"); }

    free(gv->ptr);

    *gv = (Gvec){0};
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

Multvec mv_new ( size_t s, size_t n ) {

    if (s == 0) { critical("Can't initialize a multivec with 0 sized elements");}
    if (n == 0) { critical("Can't initialize a 0 arrays multvec"); }

    void* ptr = malloc( DEFAULT_MV_CAPACITY * s * n );

    return (Multvec){ 
        .ptr = ptr, 
        .elem_size = s, 
        .arrays_len = 0, 
        .n_arrays = n, 
        .cap = DEFAULT_GV_CAPACITY
    };
}

Multvec     mv_with_cap( size_t s, size_t n, size_t cap ) {
    if (s == 0){ critical("Can't initialize a multivec with 0 sized elements");}
    if (n == 0) { critical("Can't initialize a 0 arrays multvec"); }
    if (cap == 0)      { critical("Can't initialize a 0 cap multvec"); }

    double* ptr = malloc( cap * s * n );

    return (Multvec){ 
        .ptr = ptr, 
        .elem_size = s, 
        .arrays_len = 0, 
        .n_arrays = n, 
        .cap = cap
    };
};

void mv_push_all( Multvec* mv, Gvec* gv ) {
    if ( mv  == NULL    ) { critical("Mv pointer was nullptr"); }
    if ( mv_is_null(mv) ) { critical("Mv provided was uninitialized or freed"); }
    if ( gv == NULL  )    { critical("Elem to push was nullptr"); }
    if ( gv_is_null(gv))  { critical("Elem to push was uninitialized or freed"); }
    if ( gv->len < mv->n_arrays ) { critical("Too few elements in array to push to mvarray");}

    if ( mv->arrays_len == mv->cap ) { 
        mv->cap *= 2;
        
        mv->ptr = realloc(mv->ptr, mv->cap * mv->elem_size * mv->n_arrays );
    }

    u8* mv_ptr   = mv->ptr;
    mv_ptr      += mv->arrays_len * mv->elem_size;

    for ( size_t i = 0; i < mv->arrays_len; i++ ) {
        memcpy( mv_ptr,  gv_get_ref(gv, i), mv->elem_size);
        mv_ptr += mv->cap * mv->elem_size;
    }

    mv->arrays_len++;

    return;
}

void *mv_get_ref( Multvec *mv, size_t i, size_t j)
{
    if ( mv  == NULL    ) { critical("Mv pointer was nullptr"); }
    if ( mv_is_null(mv) ) { critical("Mv provided was uninitialized or freed"); }
    if ( i >= mv->n_arrays ) { critical("Tried to access array OOB");}
    if ( j >= mv->arrays_len){ critical("Tried to access object OOB");}

    return (u8*)(mv->ptr) + (i * mv->cap * mv->elem_size) + (mv->elem_size * j); 
}

Gvec mv_get_vec(Multvec *mv, size_t i)
{
    if ( mv  == NULL    ) { critical("Mv pointer was nullptr"); }
    if ( mv_is_null(mv) ) { critical("Mv provided was uninitialized or freed"); }
    if ( i >= mv->n_arrays ) { critical("Tried to access array OOB");}

    return (Gvec){
        .cap = mv->cap, 
        .elem_size = mv->elem_size, 
        .len = mv->arrays_len, 
        .ptr = (u8*)(mv->ptr) + i*mv->cap
    };
}

Gvec mv_get_slc(Multvec *mv, size_t i)
{
    if ( mv  == NULL    ) { critical("Mv pointer was nullptr"); }
    if ( mv_is_null(mv) ) { critical("Mv provided was uninitialized or freed"); }
    if ( i >= mv->arrays_len ) { critical("Tried to access element OOB");}

    u8* mv_ptr   = mv->ptr;
    mv_ptr      += i * mv->elem_size;

    Gvec ret = gv_with_cap(mv->elem_size, mv->n_arrays);

    for ( size_t j = 0; j < mv->n_arrays; j++ ) {
        gv_push(&ret, mv_ptr);
        mv_ptr += mv->cap * mv->elem_size;
    }

    return ret;
}

void mv_destroy(Multvec *mv) {
    if ( mv  == NULL    ) { critical("Mv pointer was nullptr"); }
    if ( mv_is_null(mv) ) { critical("Mv provided was uninitialized or already freed"); }

    free(mv->ptr);

    *mv = (Multvec){0};
};