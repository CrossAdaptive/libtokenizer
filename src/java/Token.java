public class Token {

Tokenizer     t;
String        content;
int           length;
TokenGroup    group;
EnumTokenType type;

public Token( Tokenizer t, String content, TokenGroup aGroup )
{
    this.t       = t;
    this.content = content;
    this.length  = content.length();
    this.group   = aGroup;
    this.type    = DetermineTokenType( aGroup, content );
}

