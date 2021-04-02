#include <stdio.h>

#include "Libtokenizer/InputStream.h"
#include "Libtokenizer/String.h"

InputStream* InputStream_new( const char* filepath )
{
    InputStream* self = calloc( 1, sizeof( InputStream ) );

    if ( self )
    {
        self->filepath = StringCopy( filepath );
    }
    return self;
}

