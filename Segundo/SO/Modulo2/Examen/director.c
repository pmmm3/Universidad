//Nombre : Pablo Mariano
//Apellidos : Moreno Mancebo
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd[2];//Entradas,salidas del cauce
    int leidos;
    int fd_crear;
	umask(0);
	pipe(fd);
    if (argc <= 1)
    {
        fprintf(stderr, "Argumentos incorrectos\n");
        exit(1);
    }

    DIR *directorio;
    struct dirent *entrada;
    struct stat st;
    char ruta[512];
    mode_t permisos;
    int args=argc;
    int num=0;	
    while (args>1)
    {
	if (S_ISDIR(argv[args]))
	{
		num++;
	}
	args--;
    }
    int n_pids=num;
    pid_t pids[num];

	while (n_pids>0)
	{
		if ((pids[n_pids]=fork()==0)//Hijos
		{
			close(fd[0]);//Cierro la lectura
			execlp("./contenidoRegulares","FSal",getpid());


			close(fd[0]);//Cierro la escritura
	
		}
	}

//Padre
	for (int i = 0 ; i <num;i++)
	{
		wait(NULL);
		
	}
