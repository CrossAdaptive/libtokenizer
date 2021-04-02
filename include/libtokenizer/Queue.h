#ifndef LIBTOKENIZER_QUEUE_H
#define LIBTOKENIZER_QUEUE_H

#include "libtokenizer/Array.h"

typedef struct _Queue
{
    Array* inner;

} Queue;

Queue* Queue_new       ();
Queue* Queue_free      ( Queue* self );
Queue* Queue_addHead   ( Queue* self, void* object );
Queue* Queue_addTail   ( Queue* self, void* object );
void*  Queue_removeHead( Queue* self );
int    Queue_getLength ( Queue* self );

#endif

