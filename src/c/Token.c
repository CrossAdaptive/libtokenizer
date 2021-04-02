#include <stdlib.h>
#include <stdio.h>
#include "libtokenizer/Runtime.h"
#include "libtokenizer/String.h"
#include "libtokenizer/Term.h"
#include "libtokenizer/Token.h"

EnumTokenType   Token_DetermineTokenType       ( TokenGroup* group, const char* content );
EnumTokenType   Token_DetermineWhitespaceType  ( const char* content );
EnumTokenType   Token_DetermineSymbolicType    ( const char* content );
EnumTokenType   Token_DetermineAlphanumericType( const char* content );
EnumTokenType   Token_DetermineOpenType        ( const char* content );
EnumTokenType   Token_DetermineCloseType       ( const char* content );

Token* Token_new( Tokenizer* t, const char* content, TokenGroup* aGroup )
{
    Token* self = Runtime_Calloc( 1, sizeof(Token) );

    if ( self )
    {
        self->t       = t;
        self->content = StringCopy  ( content );
        self->length  = StringLength( content );
        self->group   = TokenGroup_copy( aGroup );
        self->type    = Token_DetermineTokenType( aGroup, content );
    }
    return self;
}

Token* Token_free( Token* self )
{
    if ( self->group ) self->group = TokenGroup_free( self->group );

    free( self->content );

    self->t       = NULL;
    self->content = NULL;

    Runtime_Free( self );

    return NULL;
}

const char* Token_getContent( Token* this )
{
    return this->content;
}

int Token_getLength( Token* this )
{
    return this->length;
}

TokenGroup* Token_getTokenGroup( Token* this )
{
    return this->group;
}

EnumTokenType Token_getTokenType( Token* this )
{
    return this->type;
}

EnumTokenType Token_DetermineTokenType( TokenGroup* group, const char* content )
{
    EnumTokenType type = UNKNOWN_TYPE;

    switch ( group->groupType )
    {
    case UNKNOWN_GROUP:
        type = UNKNOWN_TYPE;
        break;

    case WHITESPACE:
        type = Token_DetermineWhitespaceType( content );
        break;

    case OPEN:
        type = Token_DetermineOpenType( content );
        break;

    case CLOSE:
        type = Token_DetermineCloseType( content );
        break;

    case SYMBOLIC:
        type = Token_DetermineSymbolicType( content );
        break;

    case ALPHANUMERIC:
        type = Token_DetermineAlphanumericType( content );
        break;

    case STRING:
        type = UNKNOWN_TYPE;
        break;

    case CHAR:
        type = FLOAT;
        break;

    case VALUE:
        type = FLOAT;
        break;

    case HEX_VALUE:
        type = HEX;
        break;

    default:
        type = UNKNOWN_TYPE;
    }

    return type;
}

EnumTokenType Token_DetermineWhitespaceType( const char* content )
{
    switch( content[0] )
    {
    case ' ':
        return SPACE;
    case '\t':
        return TAB;
    case '\n':
        return NEWLINE;
    default:
        return UNKNOWN_WHITESPACE;
    }
}

EnumTokenType Token_DetermineOpenType( const char* content )
{
    switch ( content[0] )
    {
    case '{':
        return STARTBLOCK;
    case '(':
        return STARTEXPRESSION;
    case '[':
        return STARTSUBSCRIPT;
    case '<':
        return STARTTAG;
    default:
        return UNKNOWN_OPEN;
    }
}

EnumTokenType Token_DetermineCloseType( const char* content )
{
    switch ( content[0] )
    {
    case '}':
        return ENDBLOCK;
    case ')':
        return ENDEXPRESSION;
    case ']':
        return ENDSUBSCRIPT;
    case '>':
        return ENDTAG;
    default:
        return UNKNOWN_OPEN;
    }
}

EnumTokenType Token_DetermineSymbolicType( const char* content )
{
    switch ( content[0] )
    {
    case '~':   return SYMBOL;
    case '!':
        switch ( content[1] )
        {
        case '=':  return INFIXOP;
        default:   return PREFIXOP;
        }
        break;

    case '@':   return SYMBOL;
    case '#':   return SYMBOL;
    case '$':   return SYMBOL;
    case '%':
        switch ( content[1] )
        {
        case '=':  return ASSIGNMENTOP;
        default:   return INFIXOP;
        }
        break;

    case '^':
        switch ( content[1] )
        {
        case '=':  return ASSIGNMENTOP;
        default:   return INFIXOP;
        }
        break;

    case '&':
        switch ( content[1] )
        {
        case '&':  return INFIXOP;
        case '=':  return ASSIGNMENTOP;
        default:   return INFIXOP;
        }
        break;

    case '*':
        switch ( content[1] )
        {
        case '=':  return ASSIGNMENTOP;
        default:   return INFIXOP;
        }
        break;

    case '-':
        switch ( content[1] )
        {
        case '-':  return PREPOSTFIXOP;
        case '=':  return ASSIGNMENTOP;
        default:   return INFIXOP;
        }
        break;

    case '+':
        switch ( content[1] )
        {
        case '+':  return PREPOSTFIXOP;
        case '=':  return ASSIGNMENTOP;
        default:   return INFIXOP;
        }
        break;

    case '=':
        switch ( content[1] )
        {
        case '=':  return INFIXOP;
        default:   return ASSIGNMENTOP;
        }
        break;

    case '/':
        switch ( content[1] )
        {
        case '/':  return LINECOMMENT;
        case '*':  return COMMENT;
        case '=':  return ASSIGNMENTOP;
        default:   return INFIXOP;
        }
        break;

    case ':':   return OPERATOR;
    case ';':   return STOP;
    case '<':   return INFIXOP;
    case '>':   return INFIXOP;
    default:    return SYMBOL;
    }
}

EnumTokenType Token_DetermineAlphanumericType( const char* content )
{
         if ( StringEquals( content, "class"      ) ) return CLASS;
    else if ( StringEquals( content, "import"     ) ) return IMPORT;
    else if ( StringEquals( content, "include"    ) ) return INCLUDE;
    else if ( StringEquals( content, "interface"  ) ) return INTERFACE;
    else if ( StringEquals( content, "package"    ) ) return PACKAGE;

    else if ( StringEquals( content, "public"     ) ) return MODIFIER;
    else if ( StringEquals( content, "protected"  ) ) return MODIFIER;
    else if ( StringEquals( content, "private"    ) ) return MODIFIER;

    else if ( StringEquals( content, "bool"       ) ) return PRIMITIVE;
    else if ( StringEquals( content, "boolean"    ) ) return PRIMITIVE;
    else if ( StringEquals( content, "byte"       ) ) return PRIMITIVE;
    else if ( StringEquals( content, "char"       ) ) return PRIMITIVE;
    else if ( StringEquals( content, "const"      ) ) return PRIMITIVE;
    else if ( StringEquals( content, "double"     ) ) return PRIMITIVE;
    else if ( StringEquals( content, "float"      ) ) return PRIMITIVE;
    else if ( StringEquals( content, "int"        ) ) return PRIMITIVE;
    else if ( StringEquals( content, "integer"    ) ) return PRIMITIVE;
    else if ( StringEquals( content, "long"       ) ) return PRIMITIVE;
    else if ( StringEquals( content, "short"      ) ) return PRIMITIVE;
    else if ( StringEquals( content, "signed"     ) ) return PRIMITIVE;
    else if ( StringEquals( content, "string"     ) ) return PRIMITIVE;
    else if ( StringEquals( content, "unsigned"   ) ) return PRIMITIVE;
    else if ( StringEquals( content, "void"       ) ) return PRIMITIVE;

    else if ( StringEquals( content, "break"      ) ) return KEYWORD;
    else if ( StringEquals( content, "case"       ) ) return KEYWORD;
    else if ( StringEquals( content, "catch"      ) ) return KEYWORD;
    else if ( StringEquals( content, "default"    ) ) return KEYWORD;
    else if ( StringEquals( content, "extends"    ) ) return KEYWORD;
    else if ( StringEquals( content, "implements" ) ) return KEYWORD;
    else if ( StringEquals( content, "for"        ) ) return KEYWORD;
    else if ( StringEquals( content, "foreach"    ) ) return KEYWORD;
    else if ( StringEquals( content, "let"        ) ) return KEYWORD;
    else if ( StringEquals( content, "namespace"  ) ) return KEYWORD;
    else if ( StringEquals( content, "return"     ) ) return KEYWORD;
    else if ( StringEquals( content, "switch"     ) ) return KEYWORD;
    else if ( StringEquals( content, "try"        ) ) return KEYWORD;
    else if ( StringEquals( content, "var"        ) ) return KEYWORD;
    else                                              return WORD;
}

void Token_print( Token* self, void* stream )
{
    switch ( self->group->groupType )
    {
    case OPEN:
    case CLOSE:
    case SYMBOLIC:
        switch( self->type )
        {
        case COMMENT:
        case LINECOMMENT:
            Term_Colour( stream, COLOR_COMMENT );
            break;

        default:
            Term_Colour( stream, COLOR_BOLD );
        }
        break;

    case STRING:
        Term_Colour( stream, COLOR_STRING );
        break;

    case CHAR:
        Term_Colour( stream, COLOR_CHAR );
        break;

    case ALPHANUMERIC:
        switch ( self->type )
        {
        case PRIMITIVE:
            Term_Colour( stream, COLOR_TYPE );
            break;

        case CLASS:
        case KEYWORD:
        case MODIFIER:
            Term_Colour( stream, COLOR_MODIFIER );
            break;

        case WORD:
            Term_Colour( stream, COLOR_NORMAL );
            break;

        default:
            Term_Colour( stream, COLOR_LIGHT );
        }
        break;

    case VALUE:
        Term_Colour( stream, COLOR_VALUE );
        break;        

    case UNKNOWN_GROUP:
        Term_Colour( stream, COLOR_UNKNOWN );
        break;        

    default:
        Term_Colour( stream, COLOR_NORMAL );
    }
    fprintf( stream, "%s", self->content );
    Term_Colour( stream, COLOR_NORMAL );
}

