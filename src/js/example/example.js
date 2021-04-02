import { Tokenizer, PushbackReader } from '/resources/lib/js/libtokenizer.js';

document.getElementById( "textarea-input" ).oninput
=
function( event )
{
    var textarea  = event.target;
    var reader    = new PushbackReader( textarea.value );
    var tokenizer = new Tokenizer( reader );
    var output    = document.getElementById( "pre-output" );
        output.innerHTML = "";

    while ( tokenizer.hasMoreTokens() )
    {
        var token = tokenizer.nextToken();

        if ( "" != token.trim() )
        {
            var span = document.createElement( "SPAN" );
                span.innerHTML = token;

            output.appendChild( span );
        }
    }

    return false;
}

