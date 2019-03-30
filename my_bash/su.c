#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>

int main(int argc,char * argv[])
{
    char * sname = "root";
    if(argc == 2)
    {
        sname = argv[1];
    }

    struct passwd * p = getpwnam(sname);
    if(p == NULL)
    {
        perror("getpwnam error");
        exit(0);
    }

    pid_t pid = fork();
    assert(pid != -1);

    if( pid == 0)
    {
        setgid(p->pw_gid);
        setuid(p->pw_uid);
        setenv("HOME",p->pw_dir,1);

        execl(p->pw_shell,p->pw_shell,(char *) 0);

        exit(0);
    }

    wait(NULL);
    exit(0);
}

