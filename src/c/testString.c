#include <stdio.h>
#include "libtokenizer/String.h"

int main( int argc, char** argv )
{
    String* test = String_new( NULL, "Test" );

    String_free( &test );

    if ( 0 != test )
    {
        printf( "Can still see string.\n" );
    }
}

