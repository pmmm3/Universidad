#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Argumentos incorrectos\n");
        exit(1);
    }

    DIR *directorio;
    struct dirent *entrada;
    struct stat st;
    char ruta[512];
    mode_t permisos;

    if ((directorio = opendir(argv[1])) == NULL)
    {
        perror("opendir");
        exit(1);
    }

    while ((entrada = readdir(directorio)) != NULL)
    {
        sprintf(ruta, "%s/%s", argv[1], entrada->d_name);
        if (stat(ruta, &st) < 0)
        {
            perror("stat");
            exit(1);
        }
        if (S_ISREG(st.st_mode))
        {
            if ((st.st_mode & S_IWOTH) == S_IWOTH)
            {
                permisos = st.st_mode & (~S_IWOTH);
            }
            else
            {
                permisos = st.st_mode | S_IWOTH;
            }
            if (chmod(ruta, permisos) < 0)
            {
                perror("chmod");
                exit(1);
            }
        }
    }
    closedir(directorio);
}