#ifndef LIBTOKENIZER_PUSHBACKREADER_H
#define LIBTOKENIZER_PUSHBACKREADER_H

typedef struct _PushbackReader
{
    char* content;
    int   head;
    int   length;

} PushbackReader;

PushbackReader* PushbackReader_new     ( const char*      filepath );
PushbackReader* PushbackReader_free    ( PushbackReader** self     );
int             PushbackReader_read    ( PushbackReader*  self     );
PushbackReader* PushbackReader_pushback( PushbackReader*  self     );

#endif

