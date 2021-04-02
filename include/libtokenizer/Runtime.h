#ifndef LIBTOKENIZER_RUNTIME_H
#define LIBTOKENIZER_RUNTIME_H

#include <stdlib.h>

void* Runtime_Calloc( size_t count, size_t size );
void* Runtime_Free  ( void* ptr  );
int   Runtime_Allocated();

#endif

