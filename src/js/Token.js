function Token( t, content, length, aGroup )
{
    this.t       = t;
    this.content = content;
    this.length  = content.length;
    this.group   = aGroup;
    this.type    = Token.DetermineTokenType( aGroup, content );
}

Token.prototype.getContent
=
function()
{
    return this.content;
}

Token.prototype.getLength
=
function()
{
    return this.length;
}

Token.prototype.getTokenGroup
=
function()
{
    return this.group;
}

Token.prototype.getTokenType
=
function()
{
    return this.type;
}

Token.DetermineTokenType
=
function( group, content )
{
    var type = TokenType.UNKNOWN;

    switch( group )
    {
    case TokenGroup.WHITESPACE:
        type = Token.DetermineWhitespaceType( content );
        break;



    case TokenGroup.SYMBOLIC:
        type = Token.DetermineSymbolicType( content );
        break;

    case TokenGroup.ALPHANUMERIC:
        type = Token.DetermineAlhanumericType( content );
        break;

    case TokenGroup.VALUE:
        type = TokenType.VALUE;
        break;

    case TokenGroup.HEX_VALUE:
        type = TokenType.HEX;
        break;
    }
}

