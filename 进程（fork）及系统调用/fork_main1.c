# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <assert.h>


int main(int argc,char* argv[],char* envp)
{
    fork() || fork();//
    printf("A\n");
    exit(0);
}
