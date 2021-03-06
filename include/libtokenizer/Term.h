#ifndef LIBTOKENIZER_TERM_H
#define LIBTOKENIZER_TERM_H

#define COLOR_NORMAL   "\033[00m"
#define COLOR_BOLD     "\033[01m"
#define COLOR_LIGHT    "\033[02m"
#define COLOR_STRING   "\033[33m"
#define COLOR_TYPE     "\033[36m"
#define COLOR_MODIFIER "\033[94m"
#define COLOR_VALUE    "\033[33m"
#define COLOR_CHAR     "\033[33m"
#define COLOR_COMMENT  "\033[32m"
#define COLOR_UNKNOWN  "\033[41m"

void Term_Colour( void* stream, const char* color );

#endif

