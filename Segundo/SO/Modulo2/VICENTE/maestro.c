#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

struct info{
	ino_t res_inodo;
	off_t res_size;
};

int main(int argc, char*argv[]){
	int fd;
	pid_t pid;
	int n_hijos = atoi(argv[1]);
	struct info suma;

	if(mkfifo("MIFIFO", S_IRUSR | S_IWUSR) < 0){
        perror("error en mkfifo");
        exit(1);
    }

	for(int i = 0; i < n_hijos; i++){
		if((pid = fork()) < 0){
		    perror("error en fork");
		    exit(1);
		}
		else if(pid == 0){
			execlp("./esclavo", "./esclavo", NULL);
			perror("Error en exec");			
			exit(1);
		}
	}


	for(int i = 0; i < n_hijos; i++){
		wait(NULL);
	}


	if((fd = open("MIFIFO", O_RDONLY))  < 0){
            perror("error en open");
            exit(1);
    }
	
	for(int i = 0; i < n_hijos -1; i++){
		if(read(fd, &suma, sizeof(suma)) < 0){
			perror("error en read");
		    exit(1);
		}
		
		printf("Res hijo nº%d --> inodo: %ld, size: %ld", i, suma.res_inodo, suma.res_size);
	}

	close(fd);
	unlink("MIFIFO");
}
