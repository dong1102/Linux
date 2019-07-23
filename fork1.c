#include<stdio.h>
#include<unistd.h>

//判断是第几个产生的进程
int main()
{
	int tmp = 3;
	pid_t pid;
	int i = 0;
	for(; i < tmp; i++)
	{
       		pid = fork();
		if(pid == 0)//如果是子进程，则跳出循环，防止子进程创建孙子进程；
		{
			break;
		}
    	}
	//每次子进程创建完成之后，都会跳出循环，所以用i来判断子进程是第几个产生的；
	if(i == 0)//第一个子进程
	{
		printf("child1_pid=:%d\n",getpid());
	}
	if(i == 1)//第二个
	{
		printf("child2_pid=:%d\n",getpid());
	}
	if(i == 2)//第三个
	{
		printf("child3_pid=:%d\n",getpid());
	}
	
	return 0;
}
#if 0
//创建3个子进程
int main()
{
	int tmp = 3;
	pid_t pid;
	int i = 0;
	for(; i < tmp; i++)
	{
       		pid = fork();
		if(pid == 0)//如果是子进程，则跳出循环，防止子进程创建孙子进程；
		{
			break;
		}
    	}
	if(pid == 0)//判断产生了几个子进程；
	{
		printf("child\n");
	}

	return 0;
}
#endif
