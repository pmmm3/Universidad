#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

int main()
{
    int fd[2];
    DIR *directorio;
    struct dirent *entrada;
    struct stat st;
    ino_t inodo;
    off_t size;
    pid_t pid;

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
        int fin = 0;
        close(fd[0]);
        if ((directorio = opendir(".")) == NULL)
        {
            perror("opendir");
            exit(1);
        }
        while ((entrada = readdir(directorio)) != NULL && !fin)
        {
            if (stat(entrada->d_name, &st) < 0)
            {
                perror("stat");
                exit(1);
            }
            if (S_ISREG(st.st_mode))
            {
                if (write(fd[1], &st.st_ino, sizeof(st.st_ino)) < 0)
                {
                    perror("write");
                    exit(1);
                }
                fin = 1;
            }
        }
        closedir(directorio);
        exit(0);
    }
    else
    {
        close(fd[1]);
        int fin = 0;
        if (read(fd[0], &inodo, sizeof(inodo)) < 0)
        {
            perror("read");
            exit(1);
        }

        if ((directorio = opendir(".")) == NULL)
        {
            perror("opendir");
            exit(1);
        }
        while ((entrada = readdir(directorio)) != NULL && !fin)
        {
            if (entrada->d_ino == inodo)
            {
                if (stat(entrada->d_name, &st) < 0)
                {
                    perror("stat");
                    exit(1);
                }
                size = st.st_size;
                fin = 1;
            }
        }
        printf("inodo: %llu - size: %lld\n", inodo, size);
        closedir(directorio);
    }
}