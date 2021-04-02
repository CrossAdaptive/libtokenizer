#include <stdlib.h>
#include <string.h>

#include "libtokenizer/Runtime.h"
#include "libtokenizer/String.h"

String* String_new( String* self, const char* content )
{
    if ( !self ) self = Runtime_Calloc( 1, sizeof( String ) );

    if ( self )
    {
        self->content = StringCopy  ( content );
        self->length  = StringLength( content );
    }
    return self;
}

String* String_free( String** _self )
{
    String* self = *_self;

    if ( self )
    {
        free( self->content ); self->content = 0;
        self->length = 0;

        self = Runtime_Free( self );
    }

    *_self = 0;

    return self;
}

const char* String_content( const String* self )
{
    return self->content;
}

int String_length( const String* self )
{
    return self->length;
}

String* String_copy( const String* self )
{
    return String_new( NULL, self->content );
}

String* String_cat( const String* self, const String* other )
{
    char* tmp = StringCat( self->content, other->content );
    String* ret = String_new( NULL, tmp );
    free( tmp );

    return ret;
}

bool String_equals( const String* self, const String* other )
{
    return StringEquals( self->content, other->content );
}

int StringLength( const char* s )
{
    return strlen( s );
}

char* StringCopy( const char* s )
{
    int   len  = StringLength( s ) + 2;
    char* copy = calloc( len, sizeof( char ) );

    return strcpy( copy, s );
}

char* StringCat( const char* s1, const char* s2 )
{
    int len1 = StringLength( s1 );
    int len2 = StringLength( s2 );
    int len  = len1 + len2 + 1;

    char* concatenated = calloc( len, sizeof( char ) );

    int t=0;

    for ( int i=0; i < len1; i++ )
    {
        concatenated[t++] = s1[i];
    }

    for ( int i=0; i < len2; i++ )
    {
        concatenated[t++] = s2[i];
    }

    concatenated[t] = '\0';

    return concatenated;
}

bool StringEquals( const char* s1, const char* s2 )
{
    return (0 == strcmp( s1, s2 ));    
}

