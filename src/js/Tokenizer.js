export function Tokenizer( reader )
{
    this.reader = reader;
    this.queue  = new Queue();

    this.primeQueue();
}

Tokenizer.prototype.nextToken
=
function()
{
    this.primeQueue();

    if (this.queue.getLength() > 0 )
    {
        return this.queue.removeHead();
    }
    else
    {
        return undefined;
    }
}

Tokenizer.prototype.hasMoreTokens
=
function()
{
    return (this.queue.getLength() > 0);
}

Tokenizer.prototype.primeQueue
=
function()
{
    var token;

    if ( (token = this.next()) )
    {
        this.queue.addTail( token );
    }
}

Tokenizer.prototype.next
=
function()
{
    var token = "";
    var ch;
    var ch2;

    if ( (ch = this.reader.read()) )
    {
        var group = new TokenGroup( ch );

        token = token + ch;

        while ( (ch2 = this.reader.read()) )
        {
            if ( group.matches( ch2 ) )
            {
                token = token + ch2;
            }
            else
            if ( "STRING" == group.groupType )
            {
                token = token + ch2;
                this.reader.read();
                break;
            }
            else
            if ( "CHAR" == group.groupType )
            {
                token = token + ch2;
                this.reader.read();
                break;
            }
            else
            {
                break;
            }
        }
        this.reader.pushback();
    }
    return ("" == token) ? undefined : token;
}

