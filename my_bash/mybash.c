# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <assert.h>
# include <pwd.h>

# define MAX   10
# define PATH  "/home/djh/cy1706/0608/mybin/"


void printf_sys_info()
{
    char buff[128] = {0};
    int myuid = getuid();
    struct passwd * ptr = getpwuid(myuid);
    if(ptr == NULL)
    {
        printf("mybash>>");
        fflush(stdout);

        return ;
    }

    char hostname[128] = {0};
    gethostname(hostname,128);

    char cur_dir[128] = {0};
    getcwd(cur_dir,128);
    char *last_name = "/";
    char * s = strtok(cur_dir,"/");

    while(s != NULL)
    {
        last_name = s;
        s = strtok(NULL,"/");

    }

    char * user = "$";
    if(myuid = 0)
    {
        user = "#";
    }

    printf("[%s@%s %s]%s ",ptr->pw_name,hostname,last_name,user);
    fflush(stdout);


    /*
    char buff[128] = {0};
   
    strcpy(buff,"[stu@localhost ");
    
    char cur_dir[128] = {0};
    getcwd(cur_dir,128);
    strcat(buff,cur_dir);
    strcat(buff,"]$");
    //printf("[stu@localhost ~]$");
    printf("%s",buff);
    fflush(stdout);*/
}

int main()
{
    while(1)
    {
        char buff[128] = {0};

        printf_sys_info();

        fgets(buff,128,stdin);
        buff[strlen(buff)-1] = 0;

        char * myargv[MAX] = {0};

        char * s = strtok(buff," ");
        if(s == NULL)
        {
            continue;
        }

        myargv[0] = s;
        int i = 1;

        while((s = strtok(NULL," ")) != NULL)
        {
            myargv[i++] = s;
        }

        if(strcmp(myargv[0],"exit") == 0)
        {
            break;
        }
        else if(strcmp(myargv[0],"cd") == 0)
        {
            chdir(myargv[1]);
            continue;
        }

        pid_t pid = fork();
        assert(pid != -1);

        if(pid == 0)
        {
            char path[256] = {0};

            if(strncmp(myargv[0],"./",2) != 0 && strncmp(myargv[0],"/",1) != 0)
            {
                strcpy(path,PATH);
            }

            strcat(path,myargv[0]);

            execv(path,myargv);
            perror("execvp error");
            exit(0);
        }

        wait(NULL);

    }
}








