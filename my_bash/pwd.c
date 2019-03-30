#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

int main()
{
    char buff[256] = {0};

    getcwd(buff,256);
    printf("mypwd:%s\n",buff);

    exit(0);
}

