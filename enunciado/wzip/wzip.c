#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#endif

void wzip_file(FILE *fp, int *prev, int *count)
{
    int curr;

    while ((curr = fgetc(fp)) != EOF)
    {
        // 🔧 Ignorar \r para evitar contar CRLF (\r\n) como dos caracteres
        if (curr == '\r')
            continue;

        if (*prev == EOF)
        {
            *prev = curr;
            *count = 1;
        }
        else if (curr == *prev)
        {
            (*count)++;
        }
        else
        {
            fwrite(count, sizeof(int), 1, stdout);   // escribe el conteo
            fwrite(prev, sizeof(char), 1, stdout);   // escribe el caracter
            *prev = curr;
            *count = 1;
        }
    }
}

int main(int argc, char *argv[])
{
    int prev = EOF;
    int count = 0;

#ifdef _WIN32
    _setmode(_fileno(stdout), _O_BINARY);  // evitar \n -> \r\n en stdout
#endif

    if (argc == 1)
    {
        printf("wzip: file1 [file2 ...]\n");
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "rb");
        if (!fp)
        {
            printf("wzip: cannot open file\n");
            return 1;
        }
        wzip_file(fp, &prev, &count);
        fclose(fp);
    }

    if (prev != EOF)
    {
        fwrite(&count, sizeof(int), 1, stdout);
        fwrite(&prev, sizeof(char), 1, stdout);
    }

    return 0;
}
