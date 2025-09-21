#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#endif

/*
 * wunzip: Descomprime archivos comprimidos con wzip (Run Length Encoding).
 *
 * Uso:
 *   ./wunzip archivo1.z archivo2.z ...
 *
 * Regla:
 *  - Cada archivo comprimido contiene pares (int count, char c).
 *  - Leer esos pares y escribir "c" repetido "count" veces en stdout.
 *  - Retorna 0 si todo funciona, 1 si hay error de apertura.
 */

int main(int argc, char *argv[])
{
#ifdef _WIN32
    // Forzar stdout a binario para no meter CRLF
    _setmode(_fileno(stdout), _O_BINARY);
#endif

    if (argc < 2)
    {
        printf("wunzip: file1 [file2 ...]\n");
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "rb"); // abrir en modo binario
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
