#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int num_cli, finalizados = 0;

struct PeticionAtomica
{
    int n;
    char tipo;
    pid_t pid;
};

void manejador(int s)
{
    pid_t pid = wait(NULL);
    printf("Ha finalizado el hijo %d\n", pid);
    finalizados++;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Arg. incorrectos\n");
        exit(1);
    }
    int fd;
    struct PeticionAtomica peticion;
    pid_t pid, clientes[100];
    char ruta[512];
    struct sigaction sa;
    sa.sa_handler = manejador;
    sa.sa_flags = 0;

    if (sigaction(SIGCHLD, &sa, NULL) < 0)
    {
        perror("sigaction");
        exit(1);
    }

    num_cli = strtol(argv[1], NULL, 0);
    // num_cli = atoi(argv[1]);

    if (mkfifo("FIFOpet", S_IRUSR | S_IWUSR) < 0)
    {
        perror("mkfifo");
        //exit(1);
    }

    for (int i = 0; i < num_cli; i++)
    {
        if ((pid = fork()) < 0)
        {
            perror("fork");
            exit(1);
        }
        else if (pid == 0)
        {
            sprintf(ruta, "FIFO.%d", getpid());
            if (mkfifo(ruta, S_IRUSR | S_IWUSR) < 0)
            {
                perror(ruta);
                exit(1);
            }
            peticion.n = (rand() % 20) + 1;
            if ((rand() % 2 + 1) == 1)
            {
                peticion.tipo = 'i';
            }
            else
            {
                peticion.tipo = 's';
            }
            peticion.pid = getpid();

            if ((fd = open("FIFOpet", O_WRONLY)) < 0)
            {
                perror("open");
                exit(1);
            }

            if (write(fd, &peticion, sizeof(peticion)) < 0)
            {
                perror("write");
                exit(1);
            }
            close(fd);

            long long int res;

            if ((fd = open(ruta, O_RDONLY)) < 0)
            {
                perror("open");
                exit(1);
            }

            if (read(fd, &res, sizeof(res)) < 0)
            {
                perror("read");
                exit(1);
            }

            if (res == -1)
            {
                printf("Cliente %d: FALLO\n", getpid());
            }
            else if (peticion.tipo == 'i')
            {
                printf("Cliente %d: inodo %lld\n", getpid(), res);
            }
            else
            {
                printf("Cliente %d: tamaño %lld\n", getpid(), res);
            }
            close(fd);

            exit(0);
        }

        clientes[i] = pid;
    }

    if ((pid = fork()) < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)
    {
        if ((fd = open("FIFOpet", O_RDONLY)) < 0)
        {
            perror("open");
            exit(1);
        }
        if (dup2(fd, STDIN_FILENO) < 0)
        {
            perror("dup2");
            exit(1);
        }
        execl("./i17", "./i17", argv[2], NULL);
        perror("exec");
        exit(1);
    }

    while (finalizados < num_cli)
    {
        sleep(1);
    }

    unlink("FIFOpet");
    for (int i = 0; i < num_cli; i++)
    {
        sprintf(ruta, "FIFO.%d", clientes[i]);
        unlink(ruta);
    }
}