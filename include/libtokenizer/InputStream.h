#ifndef LIBTOKENIZER_INPUTSTREAM_H
#define LIBTOKENIZER_INPUTSTREAM_H

typedef struct _InputStream
{
    const char* filepath;
    void* f;

} InputStream;

InputStream* InputStream_new ( const char*  filepath );
InputStream* InputStream_free( InputStream* self     );
int          InputStream_read( InputStream* self     );

#endif

