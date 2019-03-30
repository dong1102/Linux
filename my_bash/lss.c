#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <sys/stat.h>

int main()
{
    char buff[256] = {0};
    getcwd(buff,256);

    DIR * pdir = opendir(buff);
    if(pdir == NULL)
    {
        perror("opendir error");
        exit(0);
    }

    struct dirent *p = NULL;
    while((p = readdir(pdir)) != NULL)
    {
        
    }
    exit(0);

}

