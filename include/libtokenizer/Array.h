#ifndef LIBTOKENIZER_ARRAY_H
#define LIBTOKENIZER_ARRAY_H

typedef struct _Array
{
    void** objects;
    int    length;
    int    size;

} Array;

Array* Array_new    ( Array*  self );
Array* Array_free   ( Array** self );
Array* Array_push   ( Array*  self, void* object );
void*  Array_shift  ( Array*  self );
Array* Array_unshift( Array*  self, void* object );
int    Array_length ( Array*  self );

#endif

