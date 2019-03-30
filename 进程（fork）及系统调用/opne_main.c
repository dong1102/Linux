# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <assert.h>
# include <fcntl.h>

int main()
{
    int fdr= open("passwd",O_RDONLY);
    assert(fdr != -1);
    char buff[256] = {0};
    int n = read(fdr,buff,256); 

    int fdw = open("newpasswd",O_WRONLY|O_CREAT,0600);
    assert(fdw != -1);

    while(n>0)
    {
        write(fdw,buff,n);
        n = read(fdr,buff,256);
    }
    

    close(fdr);
    close(fdw);

    exit(0);


}
