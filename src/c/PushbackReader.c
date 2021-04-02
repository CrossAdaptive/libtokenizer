#include <stdlib.h>
#include <stdio.h>
#include "libtokenizer/File.h"
#include "libtokenizer/PushbackReader.h"
#include "libtokenizer/Runtime.h"
#include "libtokenizer/String.h"

PushbackReader* PushbackReader_new( const char* filepath )
{
    PushbackReader* self = Runtime_Calloc( 1, sizeof( PushbackReader ) );

    if ( self )
    {
        self->head = 0;

        if ( File_Exists( filepath ) )
        {
            self->content = File_Get_Contents( filepath );
            self->length  = StringLength( self->content );
        }
        else
        {
            self->content = StringCopy( "" );
            self->length  = 0;
        }
    }
    return self;
}

PushbackReader* PushbackReader_free( PushbackReader* self )
{
    if ( self )
    {
        free( self->content ); self->content = 0;
        self->length = 0;

        Runtime_Free( self );
    }
    return 0;
}

int PushbackReader_read( PushbackReader* self )
{
    return (self && (self->head < self->length)) ? self->content[self->head++] : 0;
}

PushbackReader* PushbackReader_pushback( PushbackReader* self )
{
    self->head--;
    return self;
}

