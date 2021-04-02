const fs           = require( 'fs' );
const libtokenizer = require( '/Users/daniel/Documents/Dropbox/Dropspace-Sites/_CA/com.libtokenizer/_gen/lib/js/libtokenizer' );

function main()
{
    var content = fs.readFile( './test/Sample.txt', "ascii", mainHandler );
}

function mainHandler( error, content )
{
    if ( error )
    {
        console.error( error );
        return;
    }
    else
    {
        console.log( content );

        if ( true )
        {
            var reader    = new libtokenizer.PushbackReader( content );
            var tokenizer = new libtokenizer.Tokenizer     ( reader  );

            while( tokenizer.hasMoreTokens() )
            {
                token = tokenizer.nextToken();

                console.log( token );
            }
        }
    }
}

main();

