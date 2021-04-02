#include <stdlib.h>
#include "libtokenizer/Runtime.h"
#include "libtokenizer/StringBuffer.h"
#include "libtokenizer/Tokenizer.h"
#include "libtokenizer/TokenGroup.h"

static void   primeQueue( Tokenizer* self );
static Token*       next( Tokenizer* self );

Tokenizer* Tokenizer_new( PushbackReader* reader )
{
    Tokenizer* self = Runtime_Calloc( 1, sizeof( Tokenizer ) );

    if ( self )
    {   
        self->reader = reader;
        self->queue  = Queue_new();

        primeQueue( self );
    }
    return self;
}

Tokenizer* Tokenizer_free( Tokenizer* self )
{
    if ( self )
    {
        if ( 1 )
        {
            Token* tmp;

            while ( (tmp = Queue_removeHead( self->queue )) )
            {
                Token_free( tmp );
            }
        }

        self->reader = 0;

        if ( self->queue ) self->queue = Queue_free( self->queue );

        Runtime_Free( self );
    }
    return 0;
}

Token* Tokenizer_nextToken( Tokenizer* self )
{
    primeQueue( self );

    if ( Queue_getLength( self->queue ) > 0 )
    {
        return (Token*) Queue_removeHead( self->queue );
    }
    else
    {
        return NULL;
    }
}

bool Tokenizer_hasMoreTokens( Tokenizer* self )
{
    return (Queue_getLength( self->queue ) > 0);
}

static void primeQueue( Tokenizer* self )
{
    Token* token = NULL;

    if ( (token = next( self )) )
    {
        Queue_addTail( self->queue, token );
    }
}

static Token* next( Tokenizer* self )
{
    Token* token = NULL;
    int    ch    = 0;
    int    ch2   = 0;

    if ( (ch = PushbackReader_read( self->reader )) )
    {
        StringBuffer*  sb = StringBuffer_new();
        TokenGroup* group = TokenGroup_new( ch );

        sb = StringBuffer_append_char( sb, ch );

        while ( (ch2 = PushbackReader_read( self->reader )) )
        {
            if ( ESCAPE == group->groupType )
            {
                sb  = StringBuffer_append_char( sb, ch2 );
                ch2 = PushbackReader_read( self->reader );
                break;
            }
            else
            if ( TokenGroup_matches( group, ch2 ) )
            {
                if ( '\\' == ch2 )
                {
                    sb  = StringBuffer_append_char( sb, ch2 );
                    ch2 = PushbackReader_read( self->reader );
                    sb  = StringBuffer_append_char( sb, ch2 );
                }
                else
                {
                    sb  = StringBuffer_append_char( sb, ch2 );
                }
            }
            else
            if ( STRING == group->groupType )
            {
                sb = StringBuffer_append_char( sb, ch2 );
                ch2 = PushbackReader_read( self->reader );
                break;
            }
            else
            if ( CHAR == group->groupType )
            {
                sb = StringBuffer_append_char( sb, ch2 );
                ch2 = PushbackReader_read( self->reader );
                break;
            }
            else
            {
                break;
            }
        }

        if ( ch2 )
        {
            PushbackReader_pushback( self->reader );
        }

        if ( !StringBuffer_isEmpty( sb ) )
        {
            token = Token_new( self, sb->content, group );
        }

        StringBuffer_free( sb );
        TokenGroup_free( group );
    }
    return token;
}

