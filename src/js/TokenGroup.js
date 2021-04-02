function TokenGroup( character )
{
    this.character = character
    this.groupType = TokenGroup.DetermineType( character );
}

TokenGroup.DetermineType
=
function( ch )
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
    case '.':
        return EnumTokenGroup.SYMBOLIC;

    case '(':
    case '{':
    case '[':
    case '<':
        return EnumTokenGroup.OPEN;

    case ')':
    case '}':
    case ']':
    case '>':
        return EnumTokenGroup.CLOSE;

    case '"':
        return EnumTokenGroup.STRING;

    case '\'':
        return EnumTokenGroup.CHAR;

    case '_':
        return EnumTokenGroup.ALPHANUMERIC;

    default:
        var char_code = ch.charCodeAt( 0 )

        switch ( char_code )
        {
        case 10: // LF
        case 11: // VT
        case 12: // FF
        case 13: // CR
        case 14: // SO
        case 15: // SI
        case 32: // SPACE
            return EnumTokenGroup.WHITESPACE

        default:
            if ( (48 <= char_code) && (char_code <= 57) )
            {
                return EnumTokenGroup.VALUE;
            }
            else
            if ( (65 <= char_code) && (char_code <= 90) ) // uppercase
            {
                return EnumTokenGroup.ALPHANUMERIC
            }
            else
            if ( (97 <= char_code) && (char_code <= 122) ) // lowercase
            {
                return EnumTokenGroup.ALPHANUMERIC
            }
            return EnumTokenGroup.UNKNOWN;
        }
    }
}

TokenGroup.prototype.matches
=
function( character )
{
    if ( "" == character )
    {
        return false;
    }
    else
    {
        var secondType = TokenGroup.DetermineType( character );
        var char_code  = character.charCodeAt( 0 );

        switch ( this.groupType )
        {
        case EnumTokenGroup.SYMBOLIC:
            switch ( secondType )
            {
            case EnumTokenGroup.SYMBOLIC:
                return true;

            default:
                return false;
            }
            break;

        case EnumTokenGroup.STRING:
            switch ( secondType )
            {
            case EnumTokenGroup.STRING:
                return false;

            default:
                return true;
            }
            break;

        case EnumTokenGroup.CHAR:
            return false;
            break;

        case EnumTokenGroup.ALPHANUMERIC:
            switch ( secondType )
            {
            case EnumTokenGroup.ALPHANUMERIC:
            case EnumTokenGroup.VALUE:
                return true;

            default:
                return false;
            }
            break;

        case EnumTokenGroup.WHITESPACE:
            switch ( secondType )
            {
            case EnumTokenGroup.WHITESPACE:
                return true;

            default:
                return false;
            }
            break;

        case EnumTokenGroup.VALUE:
            switch ( secondType )
            {
            case EnumTokenGroup.VALUE:
                return true;

            case EnumTokenGroup.ALPHANUMERIC:
                if ( ('65' <= char_code) && (char_code <= 70) )
                {
                    return true;
                }
                else
                if ( ('97' <= char_code) && (char_code <= 102) )
                {
                    return true;
                }
                else
                return ("x" == character);

            default:
                return false;
            }
            break;

        case EnumTokenGroup.UNKNOWN:
            switch ( secondType )
            {
            case EnumTokenGroup.UNKNOWN:
                return true;

            default:
                return false;
            }
            break;

        default:
            return false;
        }
    }
}

