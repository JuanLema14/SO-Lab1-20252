#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#endif

/*
 * wgrep: Implementación simple del comando "grep".
 *
 * Uso:
 *   ./wgrep palabra archivo1 archivo2 ...
 *   ./wgrep palabra   (lee desde stdin)
 *
 * Reglas:
 *  - Si no se pasa el argumento "palabra", imprimir error y salir con código 1.
 *  - Buscar la palabra en cada línea de los archivos o stdin.
 *  - Imprimir las líneas que contengan la palabra (substring simple).
 *  - Retornar 0 si funciona correctamente, 1 si ocurre un error.
 */

int main(int argc, char *argv[])
{
#ifdef _WIN32
    _setmode(_fileno(stdout), _O_BINARY);
    _setmode(_fileno(stderr), _O_BINARY);
#endif

    // Verificar que al menos se pase la "palabra"
    if (argc < 2)
    {
        printf("wgrep: searchterm [file ...]\n");
        return 1;
    }

    char *searchterm = argv[1];
    char buffer[4096];
    int error = 0;

    // Caso 1: No hay archivo → leer de stdin
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

    // Caso 2: Hay archivos → recorrer cada uno
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
