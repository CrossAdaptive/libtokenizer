function Queue()
{
    this.inner = Array();
}

Queue.prototype.addTail
=
function( object )
{
    this.inner.push( object );
}

Queue.prototype.removeHead
=
function()
{
    return this.inner.shift();
}

Queue.prototype.addHead
=
function( object )
{
    this.inner.unshift( object );
}

Queue.prototype.getLength
=
function()
{
    return this.inner.length;
}

