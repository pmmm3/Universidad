#include <stdio.h>
#include <unistd.h>

int main()
{
    execl("./i6xx ", "./i6", "hola", NULL);
    printf("Ejecutado :)\n");
}