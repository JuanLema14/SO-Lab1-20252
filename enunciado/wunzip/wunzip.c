#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#endif


int main(int argc, char *argv[])
{
#ifdef _WIN32
    _setmode(_fileno(stdout), _O_BINARY);
#endif

    if (argc < 2)
    {
        printf("wunzip: file1 [file2 ...]\n");
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "rb");
        if (fp == NULL)
        {
            printf("wunzip: cannot open file\n");
            return 1;
        }

        int count;
        char c;
        while (fread(&count, sizeof(int), 1, fp) == 1 &&
               fread(&c, sizeof(char), 1, fp) == 1)
        {
            for (int j = 0; j < count; j++)
            {
                putchar(c);
            }
        }

        fclose(fp);
    }

    return 0;
}
