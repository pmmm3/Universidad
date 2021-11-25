#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

void Busca(char *nombreDirectorio, ino_t inodo, int enlacesRestantes)
{
    DIR *directorio;
    struct dirent *entrada;
    struct stat st;
    char ruta[4096];

    if ((directorio = opendir(nombreDirectorio)) == NULL)
    {
        perror("opendir");
        exit(1);
    }

    while ((entrada = readdir(directorio)) != NULL && enlacesRestantes)
    {
        sprintf(ruta, "%s/%s", nombreDirectorio, entrada->d_name);
        if (stat(ruta, &st) < 0)
        {
            perror(ruta);
            //exit(1);
            continue;
        }
        if (S_ISDIR(st.st_mode))
        {
            if (strcmp(entrada->d_name, ".") && strcmp(entrada->d_name, ".."))
                Busca(ruta, inodo, enlacesRestantes);
        }
        else
        {
            if (st.st_ino == inodo)
            {
                printf("%s\n", ruta);
                enlacesRestantes--;
            }
        }
    }
    closedir(directorio);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Número de argumentos incorrecto\n");
        exit(1);
    }

    struct stat st;
    if (stat(argv[1], &st) < 0)
    {
        perror("stat");
        exit(1);
    }

    Busca("/Users/vruiz", st.st_ino, st.st_nlink);
}