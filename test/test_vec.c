#include <assert.h>
#include <string.h>
#include <stdio.h>

// #include "../src/vec/vec.h"
#include "../src/vec/test.h"

int main()
{

    // #define LEN 11

    // Gvec gv = gv_with_cap(sizeof(char), LEN);
    // char str[LEN] = "brobro 69";

    // for (size_t i = 0; i < LEN; i++)
    // {
    //     gv_push(&gv, str + i);
    // }

    // assert(*(char *)gv_get_ref(&gv, 0) == str[0]);
    // assert(*(char *)gv_get_ref(&gv, 1) == str[1]);
    // assert(*(char *)gv_get_ref(&gv, 2) == str[2]);
    // assert(*(char *)gv_get_ref(&gv, 3) == str[3]);
    // assert(*(char *)gv_get_ref(&gv, 4) == str[4]);

    // assert( gv.len == gv.cap );

    #define LEN1 25

    // Gvec gv = gv_with_cap(sizeof(char), LEN);
    char str[LEN1] = "yo %% . %d .. %e .. %% .";

    Gvec ret = print_array_fmt(str, 2);

    assert( !strcmp(*(char **)gv_get_ref(&ret, 0), "yo %% . "  )   );
    assert( !strcmp(*(char **)gv_get_ref(&ret, 1), "%d .. "    )   );
    assert( !strcmp(*(char **)gv_get_ref(&ret, 2), "%e .. %% .")   );

    assert( ret.len == 3 );
    assert( ret.cap == 3 );

    Gvec yeyo = {.cap = LEN1, .len = LEN1, .elem_size = 1, .ptr = str};

    // gv_printf(&yeyo, "%c, ");

    #define LEN 5
    char ss[LEN1] = "CIAO";

    Gvec yoyo = {.cap = LEN1, .len = LEN1, .elem_size = 1, .ptr = ss};

    // gv_printf( &yoyo, "%hhu, %hhu, %hhu, %hhu, %hhu fine");

    return 0;
}