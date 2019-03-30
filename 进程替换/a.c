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
        execl("/bin/ps","ps","-f",(char*)0);
        perror("execl error");
        exit(0);
    }

    wait(NULL);
    printf("main over\n");

    /*
    printf("a pid = %d\n",getpid());

    //execl("/bin/pss","ps","-f",(char*)0);
    //execlp("ps","ps","-f",(char*)0);
    //execle("/bin/ps","ps","-f",(char*)0,envp);

    char* myargv[] = {"ps","-f",(char*)0};

    //execv("/bin/ps",myargv);
    //execvp("ps",myargv);
    execve("/bin/ps",myargv,envp);

    perror("execl error");
    
    exit(0);*/

}
