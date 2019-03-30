# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <assert.h>
# include <fcntl.h>
# include <errno.h>

int  main(int argc,char* argv[],char* envp[])
{
    printf("main pid=%d\n",getpid());

    pid_t pid = fork();
    assert(pid != -1);

    if(pid == 0)
    {
        char* myargv[] = {"b","hello","abc","123",(char*)0};
        char* myenvp[] = {"MYSTR=hello","VAL=100",(char*)0};
        execve("./b",myargv,myenvp);
        perror("execl error");
        exit(0);
        
}



}
