function Enum( array )
{
    for ( var i in array )
    {
        this[array[i]] = array[i];
    }
}

