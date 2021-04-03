#include <stdlib.h>
#include <stdio.h>

#include "libtokenizer/File.h"
#include "libtokenizer/PushbackReader.h"
#include "libtokenizer/Runtime.h"
#include "libtokenizer/String.h"

int main( int argc, char** argv )
{
    const char* filepath = "./test/Sample.txt";

    char*           c = File_Get_Contents ( filepath );
    PushbackReader* r = PushbackReader_new( filepath );
    {
        int  len = StringLength( c );
        int  i   = 0;
        char ch;

        while ( 0 != (ch = PushbackReader_read( r )) )
        {
            if ( i == len )
            {
                fprintf( stderr, "Exceeded filelength!!!" );
                exit( -1 );
            }

            if ( c[i] != ch )
            {
                fprintf( stderr, "Character mismatch: %x != %x\n", c[i], ch );
                exit( -1 );
            }

            fprintf( stdout, "#" );

            int rnum = rand();

            if ( rnum < (RAND_MAX/2) )
            {
                fprintf( stdout, "<>" );

                PushbackReader_pushback( r );
                PushbackReader_pushback( r );
                PushbackReader_pushback( r );

                PushbackReader_read( r );
                PushbackReader_read( r );
                PushbackReader_read( r );
            }
            i++;
        }
        fprintf( stdout, "\n" );
    }
    PushbackReader_free( &r );

    if ( Runtime_Allocated() )
    {
        fprintf( stderr, "Memory leak: %i\n", Runtime_Allocated() );
    }

    return 0;
}

