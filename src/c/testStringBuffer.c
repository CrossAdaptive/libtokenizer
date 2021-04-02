#include <stdio.h>
#include "libtokenizer/Runtime.h"
#include "libtokenizer/StringBuffer.h"

int main( int argc, char** argv )
{
    StringBuffer* sb = StringBuffer_new();

    for ( int i=0; i < 10; i++ )
    {
        StringBuffer_append( sb, "test" );

        const char* content = StringBuffer_content( sb );

        fprintf( stdout, "%2i: %s\n", i, content );
    }

    StringBuffer_free( sb );

    if ( Runtime_Allocated() )
    {
        fprintf( stderr, "Memory leak: %i\n", Runtime_Allocated() );
    }
}

