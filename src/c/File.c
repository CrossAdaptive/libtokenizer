#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#include "libtokenizer/File.h"

char* readline( FILE* stream );

bool File_Exists( const char* filepath )
{
    struct stat buf;

    return (0 == lstat( filepath, &buf ));
}

char* File_Get_Contents( const char* filepath )
{
    char* content = NULL;
    FILE* fp      = fopen( filepath, "r" );

    if ( fp )
    {
        struct stat buf;

        if( 0 == lstat( filepath, &buf ) )
        {
            int size = buf.st_size;

            content = calloc( size + 1, sizeof( char ) );

            int red = fread( content, size, 1, fp );
        }
    }
    return content;
}

