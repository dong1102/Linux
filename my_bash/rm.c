#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <libgen.h>
int main(int argc,char* argv[])
{
    if(argc != 2)
    printf("Usage: %s filename\n",basename(argv[0])),exit(0);
             
    if(unlink(argv[1])!=0)
    perror("unlink"),exit(-1);
                      
    //printf("unlink %s success!\n",basename(argv[1]));
    return 0;
} 
