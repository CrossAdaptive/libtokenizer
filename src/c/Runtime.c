#include <stdlib.h>
#include "libtokenizer/Base.h"
#include "libtokenizer/Runtime.h"

static int allocated = 0;

void* Runtime_Calloc( size_t count, size_t size )
{
    allocated++;

    return calloc( count, size );
}

void* Runtime_Free( void* ptr  )
{
    allocated--;

    free( ptr );

    return NULL;
}

int Runtime_Allocated()
{
    return allocated;
}

