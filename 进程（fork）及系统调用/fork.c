# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <assert.h>


int main()
{
    char *s = NULL;
    int n = 0;

    pid_t pid = fork();
    assert(pid != -1);

    if(pid == 0)
    {
	s = "child";
	n = 4;
    }
    else
    {
	s = "parent";
	n = 7;
    } 

    int i = 0;
     
    for(;i < n;i++)
    {
	printf("%d ,s=%s\n",n,s);
    }
    exit(0);
}
