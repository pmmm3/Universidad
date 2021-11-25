#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    pid_t pid;
    int fd;
    char mempadre[60], c;
    int deboescribir;

    if (mkfifo("MEMPADRE", S_IRUSR | S_IWUSR) < 0)
    {
        perror("mkfifo");
        exit(1);
    }

    sprintf(mempadre, "/proc/%d/maps", getppid());

    if ((pid = fork()) < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)
    {
        if ((fd = open("MEMPADRE", O_WRONLY)) < 0)
        {
            perror("open");
            exit(1);
        }
        if (dup2(fd, STDOUT_FILENO) < 0)
        {
            perror("dup2");
            exit(1);
        }
        execlp("cat", "cat", mempadre, NULL);
        perror("exec");
        exit(1);
    }

    if ((fd = open("MEMPADRE", O_RDONLY)) < 0)
    {
        perror("open");
        exit(1);
    }

    deboescribir = 0;
    while (read(fd, &c, sizeof(char)) > 0)
    {
        if (c == '/')
            deboescribir = 1;
        if (deboescribir)
        {
            if (write(STDOUT_FILENO, &c, sizeof(char)) < 0)
            {
                perror("write");
                exit(1);
            }
        }
        if (c == '\n')
            deboescribir = 0;
    }
}