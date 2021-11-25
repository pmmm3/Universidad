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
        if (dup2(fd[1], STDOUT_FILENO) < 0)
        {
            perror("dup2");
            exit(1);
        }
        execlp("grep", "grep", "root", "/etc/passwd", NULL);
        perror("exec");
        exit(1);
    }

    if ((pid = fork()) < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)
    {
        close(fd[1]);
        if (dup2(fd[0], STDIN_FILENO) < 0)
        {
            perror("dup2");
            exit(1);
        }
        execlp("cut", "cut", "-d:", "-f6", NULL);
        perror("exec");
        exit(1);
    }
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
}