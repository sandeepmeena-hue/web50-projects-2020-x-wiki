#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t bytes;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("usage: ./recover image\n");
        return 1;
    }
    else
    {
        FILE *inptr = fopen(argv[1], "r");
        if (inptr == NULL)
        {
            fprintf(stderr, "Could not open %s.\n", argv[1]);
            return 1;
        }
        int count = 0;
        char *filename;
        FILE *outptr;
        int *byte = calloc(1000000,512);

        while(fscanf(inptr,"%i",byte) != EOF)
        {
            if ((byte[0] == 0xff) && (byte[1] == 0xd8) && (byte[2] == 0xff) && ((byte[3] & 0xf0) == 0xe0))
            {
                if (count == 0)
                {
                    filename = "000.jpg";
                    outptr = fopen(filename,"w");
                    fwrite(byte,512,1,outptr);
                    count +=1;
                }
                else
                {
                    fclose(outptr);
                    sprintf(filename,"%03i.jpg",count);
                    count += 1;
                    outptr = fopen(filename,"w");
                    fwrite (byte,512,1,outptr);
                }
            }
            else
            {
                if (count != 0)
                {
                    fwrite (byte,512,1,outptr);
                }
            }
        }
        free(byte);
        fclose(inptr);
    }
}


