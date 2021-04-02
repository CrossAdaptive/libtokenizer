#ifndef LIBTOKENIZER_STRING_H
#define LIBTOKENIZER_STRING_H

#include "libtokenizer/Base.h"

typedef struct _String
{
    char* content;
    int   length;

} String;

String*     String_new    ( String*  self, const char* content );
String*     String_free   ( String** self );

const char* String_content( const String* self );
int         String_length ( const String* self );
String*     String_copy   ( const String* self );
String*     String_cat    ( const String* self, const String* other );
bool        String_equals ( const String* self, const String* other );

int   StringLength( const char* s                  );
char* StringCopy  ( const char* s                  );
char* StringCat   ( const char* s1, const char* s2 );
bool  StringEquals( const char* s1, const char* s2 );

#endif

