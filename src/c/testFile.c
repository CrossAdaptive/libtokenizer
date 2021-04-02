#include <stdlib.h>
#include <stdio.h>

#include "libtokenizer/File.h"

int main( int argc, char** argv )
{
    const char* filepath = "./test/Sample.txt";

    if ( ! File_Exists( filepath ) )
    {
        fprintf( stderr, "Could not find file: %s\n", filepath );
        fflush( stderr );
    }
    else
    {
        char* content = File_Get_Contents( filepath );

        fprintf( stdout, "%s\n", content );

        free( content );
    }

    return 0;
}

