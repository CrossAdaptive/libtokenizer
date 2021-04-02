#ifndef LIBTOKENIZER_FILE_H
#define LIBTOKENIZER_FILE_H

#include "libtokenizer/Base.h"

bool  File_Exists      ( const char* filepath );
char* File_Get_Contents( const char* filepath );

#endif

