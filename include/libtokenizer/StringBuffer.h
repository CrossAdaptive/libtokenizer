#ifndef LIBTOKENIZER_STRINGBUFFER_H
#define LIBTOKENIZER_STRINGBUFFER_H

#include "libtokenizer/Base.h"

typedef struct _StringBuffer
{
    char* content;
    int   length;

} StringBuffer;

StringBuffer* StringBuffer_new        ();
StringBuffer* StringBuffer_free       ( StringBuffer* self                     );
StringBuffer* StringBuffer_append     ( StringBuffer* self, const char* suffix );
StringBuffer* StringBuffer_append_char( StringBuffer* self, char        ch     );
const char*   StringBuffer_content    ( StringBuffer* self                     );
bool          StringBuffer_isEmpty    ( StringBuffer* self                     );

#endif

