# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <assert.h>
# include <fcntl.h>

int  main()
{
    int fd = opn("file",O_ERONLY | O_CREAT,0600);

    int newfd = dup2(fd,1);
    printf();



    /*close(1);

    int fd = open("file.txt",O_WRONLY | O_CREAT,0600);
    printf("fd=%d\n",fd);
    fflush(stdout);

    write(fd,"hello",5);
    printf("main over\n");
    fflush(stdout);

    close(fd);*/

    exit(0);

}
