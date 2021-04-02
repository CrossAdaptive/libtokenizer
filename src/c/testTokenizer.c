#include <stdlib.h>
#include <stdio.h>

#include "libtokenizer/Runtime.h"
#include "libtokenizer/Tokenizer.h"
#include "libtokenizer/Term.h"

void printToken( Token* self, void* stream );

int main( int argc, char** argv )
{
    const char* filepath = "./test/Sample.txt";

    PushbackReader* p = PushbackReader_new( filepath );
    Tokenizer*      t = Tokenizer_new( p );

    while ( Tokenizer_hasMoreTokens( t ) )
    {
        Token* token = Tokenizer_nextToken( t );
        {
            printToken( token, stdout );
        }
        Token_free( token );
    }

    Tokenizer_free     ( t );
    PushbackReader_free( p );

    if ( Runtime_Allocated() )
    {
        fprintf( stderr, "Memory leak: %i\n", Runtime_Allocated() );
    }
}

void printToken( Token* self, void* stream )
{
    switch ( self->group->groupType )
    {
    case OPEN:
    case CLOSE:
    case SYMBOLIC:
        switch( self->type )
        {
        case COMMENT:
        case LINECOMMENT:
            Term_Colour( stream, COLOR_COMMENT );
            break;

        default:
            Term_Colour( stream, COLOR_BOLD );
        }
        break;

    case STRING:
        Term_Colour( stream, COLOR_STRING );
        break;

    case CHAR:
        Term_Colour( stream, COLOR_CHAR );
        break;

    case ALPHANUMERIC:
        switch ( self->type )
        {
        case PRIMITIVE:
            Term_Colour( stream, COLOR_TYPE );
            break;

        case CLASS:
        case KEYWORD:
        case MODIFIER:
            Term_Colour( stream, COLOR_MODIFIER );
            break;

        case WORD:
            Term_Colour( stream, COLOR_NORMAL );
            break;

        default:
            Term_Colour( stream, COLOR_LIGHT );
        }
        break;

    case VALUE:
        Term_Colour( stream, COLOR_VALUE );
        break;        

    case UNKNOWN_GROUP:
        Term_Colour( stream, COLOR_UNKNOWN );
        break;        

    default:
        Term_Colour( stream, COLOR_NORMAL );
    }
    fprintf( stream, "%s", self->content );
    Term_Colour( stream, COLOR_NORMAL );
}

