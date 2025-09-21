#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#endif

/*
 * wcat: Implementación simple del comando "cat".
 *
 * Funcionalidades:
 *  - Si no se pasan argumentos: lee de la entrada estándar (stdin).
 *  - Si se pasan archivos como argumentos: imprime su contenido en orden.
 *  - Si un archivo no se puede abrir: imprime mensaje de error y termina.
 *  - Retorna 0 en éxito, 1 si ocurre algún error al abrir archivos.
 *
 * Notas:
 *  - En Windows, se ajusta el modo de salida a binario para evitar
 *    problemas con las terminaciones de línea (CRLF vs LF).
 *  - Se usa un buffer de 4096 bytes para leer de archivos/entrada estándar.
 */

int main(int argc, char *argv[])
{
    int error = 0; // Código de salida (0 = éxito, 1 = error al abrir archivo)

#ifdef _WIN32
    // Evita que Windows convierta "\n" en "\r\n" al imprimir
    _setmode(_fileno(stdout), _O_BINARY);
#endif

    // Caso 1: No se pasan archivos -> leer de stdin
    if (argc < 2)
    {
        char buffer[4096];
        while (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            printf("%s", buffer);
        }
        return 0; // Termina exitosamente
    }

    // Caso 2: Se pasan archivos -> imprimir en orden
    for (int i = 1; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            // Error: no se puede abrir archivo -> mensaje + salir con error
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
