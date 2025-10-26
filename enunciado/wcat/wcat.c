#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#endif

int main(int argc, char *argv[])
{
    int error = 0;

#ifdef _WIN32
    _setmode(_fileno(stdout), _O_BINARY);
#endif

    if (argc < 2)
    {
        char buffer[4096];
        while (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            printf("%s", buffer);
        }
        return 0;
    }

    for (int i = 1; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            printf("wcat: cannot open file\n");
            return 1;
        }

        char buffer[4096];
        while (fgets(buffer, sizeof(buffer), fp) != NULL)
        {
            printf("%s", buffer);
        }

        fclose(fp);
    }

    return error;
}
