#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
struct info{
	ino_t res_inodo;
	off_t res_size;
};

int main(){
	DIR* directorio;
	int fd;
	struct dirent *entrada;
	struct stat st;
	struct info suma;

	if((fd = open("MIFIFO", O_WRONLY))  < 0){
            perror("error en open");
            exit(1);
    }
	

	if((directorio = opendir(".")) == NULL){
        perror("error en opendir");
        exit(1);
    }
	
	ino_t res_inodo;
	off_t res_size;
	while((entrada = readdir(directorio)) != NULL){
        if(stat(entrada->d_name, &st) < 0){
            perror("error en stat");
            exit(1);
        }

		if(S_ISDIR(st.st_mode)){
			res_size += st.st_size;
			res_inodo += st.st_ino;
		}
	}	
	
	suma.res_inodo = res_inodo;
	suma.res_size = res_size;
	
	if(write(fd, &suma, sizeof(suma)) < 0){
    	perror("error en write");
        exit(1);
    }
	
	closedir(directorio);
}
