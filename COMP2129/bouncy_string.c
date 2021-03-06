#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main ( int argc, char *argv[] )
{
    if ( argc != 4 )
    {
        printf( "Invalid arguments length\n");
        return 1;
    }
    else if( atoi(argv[2]) < 0  || atoi(argv[2]) > strlen(argv[1]) || !isdigit((int)argv[2][0]) ) 
    {
         printf( "Invalid start position\n");
         return 1;
    }
    else if( atoi(argv[3]) < 0 )
    {    
        printf( "Invalid iteration count\n");
        return 1;
    }
    else
    {   
        int stpo = atoi( argv[ 2 ] );
        int iteco = atoi( argv[3] );
        int len = strlen( argv[1]);
        char str[ len + 1];
        strcpy( str, argv[1]);
        int isRev = 0;
        
        for(int i = 0; i <= iteco; i++ )
        {
            if(stpo < 0 )
                stpo = 0;
            putchar( str[stpo]);
            if( stpo == len - 1)
                isRev = 1;
            else if( stpo == 0 )
                isRev = 0;
            if( isRev == 1)
                stpo --;
            else
                stpo++;
        }
		printf("\n");
    }
}