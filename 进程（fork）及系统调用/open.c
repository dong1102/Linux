# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <assert.h>
# include <fcntl.h>

int main()
{
    char buff[128] = {0};

    pid_t pid = fork();
    assert(pid != -1);

    int fd = open("myfile.txt",O_RDONLY);
    if(pid == 0)
    {
        read(fd,buff,1);
        printf("child buff=%s\n",buff);

        sleep(1);
        read(fd,buff,1);
        printf("child buff=%s\n",buff);
    }
    else
    {
        read(fd,buff,1);
        printf("parent buff=%s\n",buff);

        sleep(1);
        read(fd,buff,1);
        printf("parent buff=%s\n",buff);
    }
    

    exit(0);


}
