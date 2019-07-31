#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

/*
 *pid_t waitpid(pid_t pid,int* status,in options)
 *	waitpid可设置为阻塞，也可设置为非阻塞
 *	参数：
 *	pid：
 *	   pid == -1:等待任一子进程，与wait一样；
 *	   pid > 0  :等待其进程id与pid相等的子进程；
 *	   pid == 0 :等待其组id等于调用进程的组id的任一子进程；
 *	   pid < -1 :等待其组id等于pid的绝对值的任一子进程。
 *	status：子进程的退出状态，与wait相同。
 *	options：设置为 WNOHANG 函数为非阻塞，这是为0，函数为阻塞。
 *
 *	返回值：
 *	   >0:返回清理掉的子进程的id；
 *	   -1:无子进程；
 *	   =0:参数3为WNOHANG，且子进程正在运行。
 *
 * 父进程fork三个子进程：
 *	其中一个调用ps命令；
 *	一个调用自定义应用程序；
 *	一个调用会出现段错误的程序。
 *父进程回收三个子进程（waitpid），并且打印三个子进程的退出状态。
 *
 *===段错误===
 *	1、访问了非法内存；
 *	2、访问了不可写的区域进行写操作；
 *	3、栈空间溢出
 *
 */

int main()
{
	int i = 0;
	pid_t pid;
	for(;i<3;i++)
	{
		pid = fork();
		if(pid == 0) break;
	}

	if(i == 0)
	{
		printf("子进程1：执行ps\n");
		execlp("ls","ls","-l",NULL);
		perror("execlp error");
		exit(1);	
	}
	else if(i == 1)
	{
		printf("子进程2：执行hello\n");
		execl("/home/djh/linux/hello","hello",NULL);
		perror("execl error");
		exit(1);	
	
	}
	else if(i == 2)
	{
		printf("子进程3：执行test\n");
		execl("/home/djh/linux/test","test",NULL);
		perror("execl error");
		exit(1);	
	
	}
	else if(i == 3)
	{
		pid_t wpid;
		int status;
		while((wpid = wait(&status)) != -1)
		//while((wpid = waitpid(-1,&status,WNOHANG)) != -1);
		{
			printf("父进程回收的子进程pid=：%d\n",wpid);
			if(WIFEXITED(status))
			{
				printf("exit val:%d\n",WEXITSTATUS(status)); 
			}
			else if(WIFSIGNALED(status))
	                {
        	                printf("exit by signal:%d\n",WTERMSIG(status));
               		 }

		}
	}

	return 0;
}
