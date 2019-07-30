#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

/*
 *孤儿进程：父进程先于子进程结束，子进程则称为孤儿进程。
 *	1、进程结束后，都会释放自己所占的用户空间；
 *	2、但是进程的pcb必须由父进程来释放；
 *	3、孤儿进程被系统进程init领养，释放孤儿进程的pcb。
 *
 * 僵尸进程：子进程先于父进程结束，子进程则成为僵尸进程。
 * 	1、僵尸进程是已经死掉的进程，但是它的pcb还存活在内存中；
 * 	2、子进程退出时，父进程没有及时调用wait获取子进程的退出码，释放子进程的pcb。
 *	3、僵尸进程不能用kill命令杀死，因为它是一个死了的进程；
 *	结束掉它的父进程，则僵尸进程就会被init领养，释放它的pcb。
 */
#if 0
int main()//孤儿进程
{
	pid_t pid;
	
	pid = fork();
	if(pid == 0)
	{
		sleep(1);//子进程睡眠一秒，父进程肯定先于子进程结束
		printf("child_pid=%d,ppid=%d\n",getpid(),getppid());
	}
	else if(pid > 0)
	{
		printf("parent_pid=%d\n",getpid());
	}
	return 0;
}
#endif

int main()//僵尸进程
{
	pid_t pid;
	
	pid = fork();
	if(pid == 0)
	{
		printf("child_pid=%d,ppid=%d\n",getpid(),getppid());
	}
	else if(pid > 0)
	{
		while(1)//让父进程一直忙于别的事，无暇顾及子进程。
		{
			printf("parent_pid=%d\n",getpid());
			sleep(1);
		}
	}
	return 0;
}
