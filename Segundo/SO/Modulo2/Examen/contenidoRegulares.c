//Nombre : Pablo Mariano
//Apellidos : Moreno Mancebo
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#define CHECK 
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Argumentos incorrectos\n");
        exit(1);
    }

    DIR *directorio;
    struct dirent *entrada;
    struct stat st;
    char ruta[512];
    mode_t permisos;
    
//Abrimos directorio
    if ((directorio = opendir(argv[1])) == NULL)
    {
        perror("opendir");
        exit(1);
    }
//Lectura de archivos de directorio
off_t tam;
    while ((entrada = readdir(directorio)) != NULL)
    {
    	sprintf(ruta, "%s/%s", argv[1], entrada->d_name);
        if (stat(ruta, &st) < 0)
        {
            perror("stat");
            exit(1);
        }
	if (S_ISREG(st.st_mode))
        {
		if (st.st_mode == S_IWGRP & S_IWUSR)
		{
			tam+=st.st_size;
		}	
    }
    if( (fd=open(argv[2]),O_CREAT|O_WRONLY,S_IRUSR|S_IWUSR))<0) 
    {
	sprintf(fd,"%d \n",tam);			
    }
    else
    {
	write (STDOUT_FILENO,tam,sizeof(tam));			
    }
}
	
