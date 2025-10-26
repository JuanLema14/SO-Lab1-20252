#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#endif


int main(int argc, char *argv[])
{
#ifdef _WIN32
    _setmode(_fileno(stdout), _O_BINARY);
    _setmode(_fileno(stderr), _O_BINARY);
#endif

    if (argc < 2)
    {
        printf("wgrep: searchterm [file ...]\n");
        return 1;
    }

    char *searchterm = argv[1];
    char buffer[4096];
    int error = 0;

    if (argc == 2)
    {
        while (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            if (strstr(buffer, searchterm) != NULL)
            {
                printf("%s", buffer);
            }
        }
        return 0;
    }

    for (int i = 2; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            printf("wgrep: cannot open file\n");
            return 1;
        }

        while (fgets(buffer, sizeof(buffer), fp) != NULL)
        {
            if (strstr(buffer, searchterm) != NULL)
            {
                printf("%s", buffer);
            }
        }

        fclose(fp);
    }

    return error;
}
