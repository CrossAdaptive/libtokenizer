#include <stdlib.h>
#include "libtokenizer/Queue.h"
#include "libtokenizer/Runtime.h"

static void allocArray( Queue* self )
{
    if ( !self->inner )
    {
        self->inner = Array_new( NULL );
    }
}

Queue* Queue_new()
{
    Queue* self = Runtime_Calloc( 1, sizeof( Queue ) );

    if ( self )
    {
        self->inner = Array_new( NULL );
    }
    return self;
}

Queue* Queue_free( Queue* self )
{
    if ( self )
    {
        if ( self->inner ) self->inner = Array_free( &self->inner );
        Runtime_Free( self );
    }
    return 0;
}

Queue* Queue_addHead( Queue* self, void* object )
{
    allocArray( self );

    Array_unshift( self->inner, object );

    return self;
}

Queue* Queue_addTail( Queue* self, void* object )
{
    allocArray( self );

    Array_push( self->inner, object );

    return self;
}

void* Queue_removeHead( Queue* self )
{
    allocArray( self );

    return Array_shift( self->inner );
}

int Queue_getLength( Queue* self )
{
    allocArray( self );

    return Array_length( self->inner );
}

