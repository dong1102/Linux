#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

/*
 *exec函数族：替换进程
 *1、让父子进程执行不相干的操作
 *2、换核不换壳，exec族函数，能够替换进程地址空间中的代码段.text段（对应的堆、栈中的数据都会改变），重新填充新的代码。
 *也就是说，在一个运行的程序a中，调用另外的应用程序b。
 *在执行exec族函数之前需要先fork（）；
 *
 * 引用头文件：#include<unistd.h>
 *返回值：
 *	如果exec族函数执行成功，则不返回；
 *	如果执行失败，打印错误信息，退出当前进程。
 *
 *exec函数族的函数：
 *execl：执行指定目录下的应用程序,一般用来执行自己写的程序。
 *	int execl(const char* path,const char* arg,...)execl是变参函数，
 *	path：第一个参数是需要调用的应用程序的绝对路径
 *	arg：第二个（arg）参数是程序的名字
 *	arg: 第三个(arg)参数是程序所需要的参数（没有就不要这个参数）
 *	arg: 最后一个(arg)参数就是结束标志NULL。
 *	
 *execlp:执行PATH环境变量能够搜索到的程序，一般是系统应用程序，如命令ls等。
 *	int execlp(const char* file,const char* arg,...)
 *	file:第一个参数是命令名字；
 *	arg: 第二个(arg)参数是占位
 *	arg: 第三个(arg)是参数
 *	arg: 最后一个是结束标志NULL。
 *
 */


//让父进程循环输出1~10，子进程执行hello程序
#if 0
int main()
{
	pid_t pid;
	
	int i = 0;
	for(;i < 10; i++)//父进程数数
	{
		printf("====%d====\n",i);
	}

	pid = fork();
	if(pid == 0)//子进程调用hello程序
	{
		execl("/home/djh/linux/hello","hello",NULL);
	}
	
	int j = 0;
	for(;j < 3; j++)
	{
		printf("qqq\n");
	}
	return 0;
}
#endif

//让父进程循环输出1~10，子进程执行ls命令
int main()
{
	pid_t pid;
	
	int i = 0;
	for(;i < 10; i++)//父进程数数
	{
		printf("====%d====\n",i);
	}

	pid = fork();
	if(pid == 0)//子进程调用ls
	{
		execlp("ls","ls","-a",NULL);
		perror("execlp");//如果执行失败，则打印错误信息
		exit(1);//退出当前进程
	}
	
	int j = 0;
	for(;j < 3; j++)
	{
		printf("qqq\n");
	}
	return 0;
}
