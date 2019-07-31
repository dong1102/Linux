#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

/*
 *进程间通信-----管道
 *    无名管道：适用于有血缘关系的进程之间通信（父子、兄弟等）
 *    有名管道：适用于任何进程之间
 *    原理：
 *        内部实现是环形队列，遵循先进先出的原则。
 *        环形队列的头和尾是相对的，可以移动，可以保证读取的效率。
 *        比如原队头的数据被读出，对头就会向后移，后写入的数据就会覆盖掉原队头。
 *    特点：
 *        分为读端和写端，数据从写端流入，读端流出；
 *        管道是半双工通信，数据只能在一个方向上传输；
 *        默认阻塞，读写不能同时进行。
 *    注意：
 *        数据只能读取一次，不能重复读取；
 *        单个进程也可以使用管道完成读写操作(没什么意义)；
 *        父子间进行通信不需要sleep。
 *    无名管道函数原型：
 *        int pipe(int fd[2]);
 *        fd    是传出参数；
 *        fd[0] 读端； 
 *        fd[1] 写端。
 *       
 */
//联系：
//    用代码实现命令 ps -ef | grep bash
int main()
{
	int fd[2];
	int ret = pipe(fd);//创建管道
	if(ret == -1)
	{
		perror("pipe error\n");
		exit(1);
	}

	pid_t pid = fork();//创建子进程
	if(pid > 0)//父进程执行写操作，ps -ef
	{
		close(fd[0]);//关闭读端
		dup2(fd[1],STDOUT_FILENO);//文件描述符重定向,fd[1]（管道写端）替换STDOUT_FILENO（终端输出）
		execlp("ps","ps","-ef",NULL);//进程替换
		perror("w_execlp error");
		exit(1);
	}
	if(pid == 0)//子进程执行读操作，grep bash
	{
		close(fd[1]);//关闭写端
		dup2(fd[0],STDIN_FILENO);//文件描述符重定向，
		execlp("grep","grep","--color=auto","bash",NULL);//进程替换
		perror("r_execlp error");
		exit(1);
	}

	return 0;
}
