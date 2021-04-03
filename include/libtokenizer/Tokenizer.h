#ifndef LIBTOKENIZER_TOKENIZER_H
#define LIBTOKENIZER_TOKENIZER_H

#include "libtokenizer/Base.h"
#include "libtokenizer/PushbackReader.h"
#include "libtokenizer/Queue.h"
#include "libtokenizer/Token.h"
#include "libtokenizer/TokenGroup.h"

typedef struct _Tokenizer
{
    PushbackReader* reader;
    Queue*          queue;

} Tokenizer;

Tokenizer* Tokenizer_new          ( PushbackReader** reader );
Tokenizer* Tokenizer_free         ( Tokenizer**      self   );
Token*     Tokenizer_nextToken    ( Tokenizer*       self   );
bool       Tokenizer_hasMoreTokens( Tokenizer*       self   ); 

#endif

