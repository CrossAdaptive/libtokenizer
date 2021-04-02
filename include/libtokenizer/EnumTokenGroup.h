#ifndef LIBTOKENIZER_ENUMTOKENGROUP_H
#define LIBTOKENIZER_ENUMTOKENGROUP_H

#include "libtokenizer/Base.h"

typedef enum _EnumTokenGroup
{
    UNKNOWN_GROUP,
    WHITESPACE,
    OPEN,
    CLOSE,
    SYMBOLIC,
    ESCAPE,
    ALPHANUMERIC,
    STRING,
    CHAR,
    VALUE,
    HEX_VALUE

} EnumTokenGroup;

#endif

