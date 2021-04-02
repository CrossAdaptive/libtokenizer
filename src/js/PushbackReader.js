export function PushbackReader( content )
{
    this.content  = content;
    this.head     = 0;
    this.delta    = 0;
}

PushbackReader.prototype.read
=
function()
{
    var ch = this.content[this.head++];

    this.delta = 1;

    if ( "\\" == ch )
    {
        ch += this.content[this.head++];
        this.delta = 2;
    }
    else
    if ( "'" == ch )
    {
        if ( this.content[this.head] )
        {
            ch += this.content[this.head++];
            this.delta++;
        }

        if ( this.content[this.head] )
        {
            ch += this.content[this.head++];
            this.delta++;
        }
    }

    return ch;
}

PushbackReader.prototype.pushback
=
function()
{
    this.head -= this.delta;

    this.delta = 0;
}

