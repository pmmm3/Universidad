#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

struct Info
{
    ino_t inodo;
    off_t size;
};

int main()
{
    DIR *directorio;
    struct dirent *entrada;
    struct stat st;
    off_t min, max, mitad;
    pid_t pid;
    int fd[2];
    ino_t inodo;
    off_t size;
    struct Info informacion;

    if ((directorio = opendir(".")) == NULL)
    {
        perror("opendir");
        exit(1);
    }

    if ((entrada = readdir(directorio)) == NULL)
    {
        perror("readdir");
        exit(1);
    }

    if (stat(entrada->d_name, &st) < 0)
    {
        perror("readdir");
        exit(1);
    }

    min = max = st.st_size;
    while ((entrada = readdir(directorio)) != NULL)
    {
        if (stat(entrada->d_name, &st) < 0)
        {
            perror("readdir");
            exit(1);
        }

        if (st.st_size < min)
            min = st.st_size;
        if (st.st_size > max)
            max = st.st_size;
    }
    closedir(directorio);
    mitad = (min + max) / 2;

    if (pipe(fd) < 0)
    {
        perror("pipe");
        exit(1);
    }

    if ((pid = fork()) < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)
    {
        close(fd[0]);
        max = mitad;

        if ((directorio = opendir(".")) == NULL)
        {
            perror("opendir");
            exit(1);
        }

        while ((entrada = readdir(directorio)) != NULL)
        {
            if (stat(entrada->d_name, &st) < 0)
            {
                perror("readdir");
                exit(1);
            }

            if (st.st_size >= min && st.st_size <= max)
            {
                informacion.inodo = st.st_ino;
                informacion.size = st.st_size;
                if (write(fd[1], &informacion, sizeof(informacion)) < 0)
                {
                    perror("write");
                    exit(1);
                }
            }
        }
        closedir(directorio);

        exit(0);
    }

    if ((pid = fork()) < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)
    {
        close(fd[0]);
        min = mitad + 1;

        if ((directorio = opendir(".")) == NULL)
        {
            perror("opendir");
            exit(1);
        }

        while ((entrada = readdir(directorio)) != NULL)
        {
            if (stat(entrada->d_name, &st) < 0)
            {
                perror("readdir");
                exit(1);
            }

            if (st.st_size >= min && st.st_size <= max)
            {
                informacion.inodo = st.st_ino;
                informacion.size = st.st_size;
                if (write(fd[1], &informacion, sizeof(informacion)) < 0)
                {
                    perror("write");
                    exit(1);
                }
            }
        }
        closedir(directorio);

        exit(0);
    }

    close(fd[1]);
    while (read(fd[0], &inodo, sizeof(inodo)) > 0)
    {
        if (read(fd[0], &size, sizeof(size)) < 0)
        {
            perror("read");
            exit(1);
        }

        if ((directorio = opendir(".")) == NULL)
        {
            perror("opendir");
            exit(1);
        }
        int encontrado = 0;
        while ((entrada = readdir(directorio)) != NULL && !encontrado)
        {
            if (entrada->d_ino == inodo)
            {
                encontrado = 1;

                if (stat(entrada->d_name, &st) < 0)
                {
                    perror("readdir");
                    exit(1);
                }
                if (st.st_size == size)
                {
                    printf("Correcto :)\n");
                }
                else
                {
                    printf("ERRORRRRR :|\n");
                }
            }
        }

        if (!encontrado)
        {
            printf("NO ENCONTRADO :@\n");
        }
        closedir(directorio);
    }
}