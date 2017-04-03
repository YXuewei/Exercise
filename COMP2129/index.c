#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//You may add/modify/remove structs

typedef struct pixel_t pixel_t;

struct pixel_t {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t empty;
    int index;
    pixel_t *next;
    pixel_t *prev;
};

void list_init( pixel_t *head );
void appened( pixel_t *head, pixel_t *n);
int get_element( pixel_t *n, char value );// R,G,B represents color, I represent Index

int main(int argc, char* argv[]) {
	
	if ( argc == 1)
    {
        printf("No Filename Specified\n");
        return 1;
    }

    FILE *fp;
    fp = fopen( argv[1], "r");
    if ( fp == NULL )
    {
        printf("File Does Not Exist\n");
        //perror("Failed: ");
        return 1;
    }

    int width;
    int height;
    uint16_t magic;
    fread( &width, 4, 1, fp);
    fread( &height, 4, 1, fp);
    fread( &magic, 2, 1, fp);

    if ( magic != 60535)
    {
        printf( "Invalid Image Header\n");
        return 1;
    }

    int array[ height ][ width ];
    pixel_t *mem[1000];

    for ( int i = 0; i < 1000; i++ )
    {
        mem[i] = NULL;
    }

    int read = 0;

    pixel_t *head = (pixel_t*)malloc( 16 * sizeof( int ) );
    pixel_t *warden = head;
    list_init( head);
    int count = 0;
    int is_freed = 0;
    int width_po = -1;
    int height_po = -1;

    while ( 1)
    {
        is_freed = 0;
        fread( &read, 1, 1, fp);
        if ( feof(fp) )
        {
            break;
        }
        pixel_t *node = (pixel_t*)malloc( 16 * sizeof( int ) );
        node->red = read;
        fread( &read, 1, 1, fp);
        node->green = read;
        fread( &read, 1, 1, fp);
        node->blue = read;
        fread( &read, 1, 1, fp);
        node->empty = read;
        
        if ( width_po == width - 1)
        {
            width_po = 0;
            height_po++;
        }
        else
        {
            width_po++;
            if( height_po < 0 )
            {
                height_po = 0;
            }
        }

        head = warden->next;

        for ( int i = 0; i < count + 1; i++ )
        {
            if ( warden->next == NULL )
            {
                appened( warden, node);
                node->index = count;
                read = count;
                mem[count] = node;
                is_freed = 1;
            }
            else
            {
                if ( head->red == node->red )
                {
                    if ( head->green == node->green )
                    {
                        if ( head->blue == node->blue )
                        {
                            read = head->index;
                            free( node );
                            is_freed = 1;
                            break;
                        }
                    }
                }
                if ( i != count )
                {
                    head = head->next;
                }
            }
        }

        if ( is_freed == 0 )
        {
            count++;
            appened( head, node );
            node->index = count;
            array[height_po][width_po] = count;
            mem[count] = node;
        }
        else
        {
            //printf("%d       %d\n", height_po, width_po);
            array[height_po][width_po] = read;
        }
    }

    fclose( fp );

    if ( (height_po != height - 1) || ( width_po != width - 1) )
    {
        printf("Invalid Image Data\n");
        return 1;
    }
    //printf("count is %d\n", count);
    for ( int i = 0; i < height; i++ )
    {
        printf("["); 
        for ( int j = 0; j < width; j++ )
        {
            if ( j == width - 1)
            {
                printf(" %d ", array[i][j] );
            }
            else
            {
                printf(" %d,", array[i][j] );
            }
        }
        printf("]\n");
    }

    for ( int i = 0; i < count + 1; i++ )
    {
        free( mem[i] );
    }

    free( warden );    
	return 0;
}

void list_init( pixel_t *head )
{
    head->next = NULL;
    head->prev = NULL;
}

void appened( pixel_t *head, pixel_t *n )
{
     if ( head->next == NULL )
    {
        head->next = n;
        n->prev = head;
    }
    else
    {
        pixel_t *temp;
        temp = head->next;
        head->next = n;
        n->prev = head;
        n->next = temp;
    }
}

int get_element( pixel_t *n, char value )
{
    switch ( value )
    {
        case 'R':
            return n->red;
        case 'B':
            return n->blue;
        case 'G':
            return n->green;
        case 'I':
            return n->index;
        default:
            return -1;
    }
}