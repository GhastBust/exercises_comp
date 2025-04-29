#include "../src/output/output.h"

#include <assert.h>

int main() {

    assert( str_count_sub("% brr brr patapim % % %%", "%") == 5);

    // printf( "%d", str_count_sub("% brr brr patapim % % %%", "%"));

    return 0;
}