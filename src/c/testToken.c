#include <stdio.h>
#include "libtokenizer/Token.h"
#include "libtokenizer/TokenGroup.h"

int main( int argc, char** argv )
{
    Token* token = Token_new( 0, "String", TokenGroup_new( 'A' ) );

    fprintf( stdout, "%s\n", Token_getContent   ( token ) );
    //fprintf( stdout, "%i\n", Token_getTokenGroup( token ) );
    fprintf( stdout, "%i\n", Token_getTokenType ( token ) );

    Token_free( token );
}

