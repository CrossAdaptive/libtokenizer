#include "libtokenizer/Base.h"
#include "libtokenizer/Runtime.h"
#include "libtokenizer/TokenGroup.h"

TokenGroup* TokenGroup_new( char character )
{
    TokenGroup* self = Runtime_Calloc( 1, sizeof( TokenGroup ) );

    if ( self )
    {
        self->character = character;
        self->groupType = TokenGroup_DetermineType( character );
    }

    return self;
}

TokenGroup* TokenGroup_free( TokenGroup* self )
{
    if ( self )
    {
        self->character = 0;
        self->groupType = 0;
    }
    Runtime_Free( self );

    return 0;
}

EnumTokenGroup TokenGroup_DetermineType( char ch )
{
    switch ( ch )
    {
    case '~':
    case '!':
    case '@':
    case '#':
    case '$':
    case '%':
    case '^':
    case '&':
    case '*':
    case '-':
    case '+':
    case '=':
    case '|':
    case ':':
    case ';':
    case ',':
    case '.':
    case '?':
    case '/':
        return SYMBOLIC;

    case '\\':
        return ESCAPE;

    case '(':
    case '{':
    case '[':
    case '<':
        return OPEN;

    case ')':
    case '}':
    case ']':
    case '>':
        return CLOSE;

    case '"':
        return STRING;

    case '\'':
        return CHAR;

    case '_':
        return ALPHANUMERIC;

    default:
        switch ( ch )
        {
        case  9: // TAB
        case 10: // LF
        case 11: // VT
        case 12: // FF
        case 13: // CR
        case 14: // SO
        case 15: // SI
        case 32: // SPACE
            return WHITESPACE;

        default:
            if ( (48 <= ch) && (ch <= 57) )
            {
                return VALUE;
            }
            else
            if ( (65 <= ch) && (ch <= 90) ) // uppercase
            {
                return ALPHANUMERIC;
            }
            else
            if ( (97 <= ch) && (ch <= 122) ) // lowercase
            {
                return ALPHANUMERIC;
            }
            return UNKNOWN_GROUP;
        }
    }
}

bool TokenGroup_matches( TokenGroup* self, char ch )
{
    if ( '\0' == ch )
    {
        return FALSE;
    }
    else
    {
        EnumTokenGroup secondType = TokenGroup_DetermineType( ch );

        switch( self->groupType )
        {
        case SYMBOLIC:
            switch( secondType )
            {
            case SYMBOLIC:
                return TRUE;

            default:
                return FALSE;
            }
            break;

        case STRING:
            switch ( secondType )
            {
            case STRING:
                return FALSE;

            default:
                return TRUE;
            }
            break;

        case CHAR:
            switch ( secondType )
            {
            case CHAR:
                return FALSE;

            default:
                return TRUE;
            }
            break;

        case ALPHANUMERIC:
            switch ( secondType )
            {
            case ALPHANUMERIC:
            case VALUE:
                return TRUE;

            default:
                return FALSE;
            }
            break;

        case WHITESPACE:
            switch ( secondType )
            {
            case WHITESPACE:
                return TRUE;

            default:
                return FALSE;
            }
            break;

        case VALUE:
            switch ( secondType )
            {
            case VALUE:
                return TRUE;

            case ALPHANUMERIC:
                if ( (65 <= ch) && (ch <= 70) )
                {
                    return TRUE;
                }
                else
                if ( (97 <= ch) && (ch <= 102) )
                {
                    return TRUE;
                }
                else
                return ('x' == ch);

            default:
                return FALSE;
            }
            break;

        case UNKNOWN_GROUP:
            switch ( secondType )
            {
            case UNKNOWN_GROUP:
                return TRUE;

            default:
                return FALSE;
            }
            break;

        default:
            return FALSE;
        }
    }
}

TokenGroup* TokenGroup_copy( const TokenGroup* self )
{
    TokenGroup* copy = Runtime_Calloc( 1, sizeof( TokenGroup ) );

    copy->character = self->character;
    copy->groupType = self->groupType;

    return copy;
}

