#include <fcntl.h>
#include <unistd.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int fd;
    if ((fd = open("mi_llave_arriba", O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU)) < 0)
    {
        perror("dios");
        exit(1);
    }
    dup2(fd, STDOUT_FILENO);
    execlp("ls", "ls", "-l", NULL);
    printf("Duplicado :)\n");
}