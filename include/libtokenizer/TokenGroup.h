#ifndef LIBTOKENIZER_TOKENGROUP_H
#define LIBTOKENIZER_TOKENGROUP_H

#include "libtokenizer/Base.h"
#include "libtokenizer/EnumTokenGroup.h"

typedef struct _TokenGroup
{
    char           character;
    EnumTokenGroup groupType;

} TokenGroup;

TokenGroup*    TokenGroup_new          ( char ch );
TokenGroup*    TokenGroup_free         ( TokenGroup* self );
EnumTokenGroup TokenGroup_DetermineType( char ch );
bool           TokenGroup_matches      ( TokenGroup* self, char ch );
TokenGroup*    TokenGroup_copy         ( const TokenGroup* self );

#endif

