#include <stdlib.h>
#include "libtokenizer/Array.h"
#include "libtokenizer/Runtime.h"

void Array_expand( Array* self )
{
    if ( 0 == self->size )
    {
        self->objects = (void**) Runtime_Calloc( 1, sizeof( void* ) );
        self->size    = 1;
    }
    else
    {
        int new_size = self->size * 2;

        void** tmp = (void**) Runtime_Calloc( new_size, sizeof( void* ) );

        for ( int i=0; i < self->length; i++ )
        {
            tmp[i] = self->objects[i];
        }

        Runtime_Free( self->objects );

        self->objects = tmp;
        self->size    = new_size;
    }
}

Array* Array_new( Array* self )
{
    if ( ! self ) self = Runtime_Calloc( 1, sizeof( Array ) );

    if ( self )
    {
        self->objects = 0;
        self->length  = 0;
        self->size    = 0;
    }
    return self;
}

Array* Array_free( Array** _self )
{
    Array* self = *_self;

    if ( self )
    {
        if ( self->objects ) Runtime_Free( self->objects );

        self->objects = 0;
        self->length  = 0;
        self->size    = 0;

        self = Runtime_Free( self );
    }

    *_self = 0;

    return 0;
}

Array* Array_push( Array* self, void* object )
{
    if ( self->length == self->size )
    {
        Array_expand( self );
    }

    self->objects[self->length++] = object;

    return self;
}

void* Array_shift( Array* self )
{
    if ( self->length )
    {
        void* head = self->objects[0];

        for ( int i=1; i < self->length; i++ )
        {    
            self->objects[i-1] = self->objects[i];
            self->objects[i]   = 0;
        }
        self->length--;
        return head;
    }
    else
    {
        return NULL;
    }
}

Array* Array_unshift( Array* self, void* object )
{
    if ( self->length == self->size )
    {
        Array_expand( self );
    }

    for ( int i=self->length; 0 < i; i-- )
    {    
        self->objects[i]   = self->objects[i-1];
        self->objects[i-1] = 0;
    }
    self->objects[0] = object;

    self->length++;

    return self;
}

int Array_length( Array* self )
{
    return self->length;
}

