#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>

/*
 *进程回收函数：
 *wait:--阻塞函数
 *pid_t wait(int* status);    
 *    1、返回值：
 *	-1：返回失败，已经没有子进程了；
 *	>0：回收的是子进程对应的pid。
 *    2、参数：
 *	判断子进程是如何死的（正常退出/被信号杀死）
 *    3、注意事项：
 *	调用一次wait只能回收一个子进程。
 *
 * 	正常结束：
 *	WIFEXITED(status):    >0 正常结束
 *	WEXITSTATUS(status);  上述宏>0时，调用此宏获取进程退出状态
 *	
 *	信号结束：
 *	WIFSIGNALED(status)： >0 异常终止（信号）
 *	WTERMSIG(status);     上述宏>0时，调用此宏获取终止进程的信号编号
 *
 *
 * */

int main()
{
	pid_t pid = fork();
	//wait(NULL);//若不关心推出状态，则将参数置为NULL
	
	if(pid == 0)
	{
		while(1)
		{
			sleep(2);//子进程睡眠2秒，判断父进程是否等待子进程退出
		}
		printf("child_pid=%d,ppid=%d\n",getpid(),getppid());
	}
	else if(pid > 0)
	{
		int status;
		pid_t wpid = wait(&status);
		//判断子进程是否正常退出
		if(WIFEXITED(status))
		{
			printf("exit val:%d\n",WEXITSTATUS(status)); 
		}
		//判断子进程是否被信号杀死
		if(WIFSIGNALED(status)) 
		{
			printf("exit by signal:%d\n",WTERMSIG(status));
		}
		
		printf("dide child pid=%d\n",wpid);
	}
	return 9;
}
