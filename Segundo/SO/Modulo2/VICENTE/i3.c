#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    for (int i = 0; i < 5; i++)
    {
        if ((pid = fork()) < 0)
        {
            perror("fork");
            exit(1);
        }
        else if (pid == 0)
        {
            printf("Mi pid=%d, el pid de mi padre=%d\n", getpid(), getppid());
            exit(0);
        }
    }
    for (int i = 0; i < 5; i++)
        wait(NULL);
    printf("PAPA=%d\n", getpid());
}