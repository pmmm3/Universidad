#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    pid_t pid;
    int fd, fdfichero, leidos;
    DIR *directorio;
    struct dirent *entrada;
    struct stat st;
    char nombre[sizeof(entrada->d_name)];
    char buffer[512];

    if (mkfifo("MIFIFO", S_IRUSR | S_IWUSR) < 0)
    {
        perror("mkfifo");
        exit(1);
    }

    if ((pid = fork()) < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)
    {
        if ((fd = open("MIFIFO", O_RDONLY)) < 0)
        {
            perror("open");
            exit(1);
        }
        while (read(fd, nombre, sizeof(nombre)) > 0)
        {
            if ((fdfichero = open(nombre, O_RDONLY)) < 0)
            {
                perror("open");
                exit(1);
            }
            while ((leidos = read(fdfichero, buffer, sizeof(buffer))) > 0)
            {
                if (write(STDOUT_FILENO, buffer, leidos) < 0)
                {
                    perror("write");
                    exit(1);
                }
            }
            close(fdfichero);
        }
        close(fd);
        exit(0);
    }

    if ((fd = open("MIFIFO", O_WRONLY)) < 0)
    {
        perror("open");
        exit(1);
    }

    if ((directorio = opendir(".")) == NULL)
    {
        perror("opendir");
        exit(1);
    }
    while ((entrada = readdir(directorio)) != NULL)
    {
        if (stat(entrada->d_name, &st) < 0)
        {
            perror("stat");
            exit(1);
        }
        if (S_ISREG(st.st_mode))
        {
            printf("I-nodo: %llu, UID: %d\n", st.st_ino, st.st_uid);
            if (st.st_mode & S_IRUSR != S_IRUSR)
            {
                if (chmod(entrada->d_name, st.st_mode | S_IRUSR) < 0)
                {
                    perror("chmod");
                    exit(1);
                }
            }
            if (write(fd, entrada->d_name, sizeof(entrada->d_name)) < 0)
            {
                perror("write");
                exit(1);
            }
        }
    }
    closedir(directorio);
}