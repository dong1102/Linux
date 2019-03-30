#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <pthread.h>

void * fun(void* arg)
{
    int i = 0;
    for(;i < 5;i++)
    {
        printf("fun run\n");
        sleep(1);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t id;

    pthread_create(&id,NULL,fun,NULL);

    int i = 0;
    for(;i<2;i++)
    {
        printf("main run\n");
        sleep(1);
    }
    exit(0);
}


