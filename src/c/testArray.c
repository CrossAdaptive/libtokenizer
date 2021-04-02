#include <stdlib.h>
#include <stdio.h>
#include "libtokenizer/Array.h"
#include "libtokenizer/Runtime.h"
#include "libtokenizer/String.h"

int main( int argc, char** argv )
{
    Array* array  = Array_new( NULL );
    Array* target = Array_new( NULL );

    int len;

    if ( 1 )
    {
        for ( int i=0; i < 100; i++ )
        {
            char* test = StringCopy( "test" );

            Array_push( array, test );
        }

        len = Array_length( array );

        //fprintf( stdout, "Removing %i items\n", len );
        for ( int i=0; i < len; i++ )
        {
            char* test = (char*) Array_shift( array );

            //fprintf( stdout, "%2i: %s\n", i, test );

            Array_unshift( target, test );
        }
        len = Array_length( array );

        //fprintf( stdout, "%i items left\n", len );

        if ( 0 != len )
        {
            fprintf( stderr, "Unusual circumstance\n" );
            exit( -1 );
        }

        if ( (char*) Array_shift( array ) )
        {
            fprintf( stderr, "Unusual circumstance\n" );
            exit( -1 );
        }
    }
    Array_free( &array );

    if ( 1 )
    {
        len = Array_length( target );
        //fprintf( stdout, "Removing %i items from target\n", len );
        for ( int i=0; i < len; i++ )
        {
            char* test = (char*) Array_shift( target );

            //fprintf( stdout, "%2i: %s\n", i, test );

            free( test );
        }
        len = Array_length( target );

        //fprintf( stdout, "%i items left\n", len );

        if ( 0 != len )
        {
            fprintf( stderr, "Unusual circumstance\n" );
            exit( -1 );
        }

        if ( (char*) Array_shift( target ) )
        {
            fprintf( stderr, "Unusual circumstance\n" );
            exit( -1 );
        }
    }
    Array_free( &target );

    if ( Runtime_Allocated() )
    {
        fprintf( stderr, "Memory leak: %i\n", Runtime_Allocated() );
    }
}

