#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int fd;

    if (mkfifo("ORIGINAL", S_IRWXU) < 0)
    {
        perror("mkfifo");
        //exit(1);
    }

    if ((pid = fork()) < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)
    {
        if ((fd = open("ORIGINAL", O_WRONLY)) < 0)
        {
            perror("open");
            exit(1);
        }
        if (dup2(fd, STDOUT_FILENO) < 0)
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
        if ((fd = open("ORIGINAL", O_RDONLY)) < 0)
        {
            perror("open");
            exit(1);
        }
        if (dup2(fd, STDIN_FILENO) < 0)
        {
            perror("dup2");
            exit(1);
        }
        execlp("cut", "cut", "-d:", "-f6", NULL);
        perror("exec");
        exit(1);
    }

    wait(NULL);
    wait(NULL);

    //unlink("ORIGINAL");
}
