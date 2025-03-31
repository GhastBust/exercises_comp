#include "vec.h"

#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

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