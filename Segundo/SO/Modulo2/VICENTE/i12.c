#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int fd;
    umask(0);
    if ((fd = open("tonto", O_WRONLY | O_CREAT | O_TRUNC, 0667)) < 0)
    {
        perror("open");
        exit(1);
    }
    if (write(fd, "mola", 4) < 0)
    {
        perror("write");
        exit(1);
    }
    close(fd);
}