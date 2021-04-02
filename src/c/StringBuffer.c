#include <stdlib.h>
#include "libtokenizer/Runtime.h"
#include "libtokenizer/String.h"
#include "libtokenizer/StringBuffer.h"

StringBuffer* StringBuffer_new()
{
    StringBuffer* self = Runtime_Calloc( 1, sizeof( StringBuffer ) );

    if ( self )
    {
        self->content = StringCopy( "" );
        self->length  = 0;
    }
    return self;
}

StringBuffer* StringBuffer_free( StringBuffer* self )
{
    free( self->content );
    self->length = 0;
    Runtime_Free( self );

    return 0;
}

StringBuffer* StringBuffer_append( StringBuffer* self, const char* suffix )
{
    self->length += StringLength( suffix );
    char* tmp = self->content;
    self->content = StringCat( tmp, suffix );
    free( tmp );

    return self;
}

StringBuffer* StringBuffer_append_char( StringBuffer* self, char ch )
{
    char suffix[2] = { ch , '\0' };

    return StringBuffer_append( self, suffix );
}

const char* StringBuffer_content( StringBuffer* self )
{
    return self->content;
}

bool StringBuffer_isEmpty( StringBuffer* self )
{
    return (0 == StringLength( self->content ));
}

