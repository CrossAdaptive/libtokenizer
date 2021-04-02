#include <stdlib.h>
#include <stdio.h>
#include "libtokenizer/Queue.h"
#include "libtokenizer/Runtime.h"
#include "libtokenizer/String.h"

int main( int argc, char** argv )
{
    Queue* q1 = Queue_new();
    Queue* q2 = Queue_new();

    int len;

    if ( 1 )
    {
        for ( int i=0; i < 100; i++ )
        {
            char* test = StringCopy( "test" );

            Queue_addTail( q1, test );
        }

        len = Queue_getLength( q1 );

        fprintf( stdout, "Removing %i items\n", len );
        for ( int i=0; i < len; i++ )
        {
            char* test = (char*) Queue_removeHead( q1 );

            fprintf( stdout, "%2i: %s\n", i, test );

            Queue_addHead( q2, test );
        }
        len = Queue_getLength( q1 );

        fprintf( stdout, "%i items left\n", len );
    }
    q1 = Queue_free( q1 );

    if ( 1 )
    {
        len = Queue_getLength( q2 );
        fprintf( stdout, "Removing %i items from target\n", len );
        for ( int i=0; i < len; i++ )
        {
            char* test = (char*) Queue_removeHead( q2 );

            fprintf( stdout, "%2i: %s\n", i, test );

            free( test );
        }
        len = Queue_getLength( q2 );

        fprintf( stdout, "%i items left\n", len );

        if ( 0 != len )
        {
            fprintf( stderr, "Unusual circumstance: length\n" );
            exit( -1 );
        }

        if ( (char*) Queue_removeHead( q2 ) )
        {
            fprintf( stderr, "Unusual circumstance: head\n" );
            exit( -1 );
        }        

        fprintf( stdout, "%i items left\n", len );
    }
    q2 = Queue_free( q2 );

    if ( Runtime_Allocated() )
    {
        fprintf( stderr, "Memory leak: %i\n", Runtime_Allocated() );
    }
}

