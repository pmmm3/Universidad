#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    pid_t pid;
    int fd[2];

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
        int numero;
        scanf("%d", &numero);
        if (write(fd[1], &numero, sizeof(int)) < 0)
        {
            perror("write");
            exit(1);
        }
    }
    else
    {
        close(fd[1]);
        int numero;
        if (read(fd[0], &numero, sizº) < 0)
        {
            perror("read");
            exit(1);
        }
        printf("Leído: %d\n", numero);
    }
}