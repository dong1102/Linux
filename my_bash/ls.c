#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <sys/stat.h>

int main()
{
    char path[128] = {0};
    getcwd(path,128);

    DIR * pdir = opendir(path);
    if(pdir == NULL)
    {
        perror("opendir error");
        exit(0);
    }

    struct dirent * p = NULL;
    struct stat st;
    while((p = readdir(pdir)) != NULL)
    {
        if(strncmp(p->d_name,".",1) == 0)
        {
            continue;
        }
        
        stat(p->d_name,&st);
        if(S_ISDIR(st.st_mode))
        {
            printf("\033[1;34m%s   \033[0m",p->d_name);
        }
        else
        {
            if(st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
            {
                printf("\033[1;32m%s   \033[0m",p->d_name);
            }
            else
            {
                printf("%s   ",p->d_name);
            }
        }
    
        fflush(stdout);
    }
    closedir(pdir);
    printf("\n");
    exit(0);

}

