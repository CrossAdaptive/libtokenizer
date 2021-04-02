#ifndef LIBTOKENIZER_TOKEN_H
#define LIBTOKENIZER_TOKEN_H

#include "TokenGroup.h"
#include "EnumTokenType.h"

typedef struct _Tokenizer Tokenizer;

typedef struct _Token
{
    Tokenizer*    t;
    char*         content;
    int           length;
    TokenGroup*   group;
    EnumTokenType type;

} Token;

Token*        Token_new                      ( Tokenizer* t, const char* content, TokenGroup* aGroup );
Token*        Token_free                     ( Token* this );
const char*   Token_getContent               ( Token* this );
TokenGroup*   Token_getTokenGroup            ( Token* this );
EnumTokenType Token_getTokenType             ( Token* this );
void          Token_print                    ( Token* this, void* stream );

#endif

