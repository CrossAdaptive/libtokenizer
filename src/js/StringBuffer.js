function StringBuffer()
{
    this.inner = "";
}

StringBuffer.prototype.append
=
function( string )
{
    this.inner += string;
}

