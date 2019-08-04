#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
/*
 *守护进程：
 *	独立于控制终端，在后台周期性的执行某些操作的进程。
 *	不受用户登录/注销影响
 *	一般采用以d结尾的名字
 *	作用：
 *		避免进程在执行过程中的信息在任何终端上显示；
 *		避免进程被任何终端所产生的终端信息所打断。
 *		通俗的说就是，想让某个进程不因为用户或终端或其他的变化而受到影响，那么就必须把这个进程变成一个守护进程。
 *	创建：
 *		1、fork子进程，终止父进程（必须执行）
 *		2、在子进程中创建新会话（必须执行，通过setsid()函数创建新会话）
 *		3、改变当前工作目录chdir(不必须，为了增强程序的健壮性)
 *		4、重设文件掩码（不必须，子进程会继承父进程的文件掩码，可以增加程序的灵活性，用umask(0)方法）
 *		5、关闭文件描述符（不必须，此进程脱离了终端，所以关闭标准输入（0）、输出（1）、错误输出（2），目的是释放资源）
 *		6、执行核心内容（必须的，守护进程存在的必要性）
 *
 */
//创建一个守护进程，每隔三秒钟获取一次系统时间，将这个时间写入磁盘文件
//思路：
//	创建子进程 -》设置定时器（三秒钟获取一次）-》捕捉信号

void dowork()
{
	//得到当前时间
	time_t curtime;
	time(&curtime);
	//格式化时间
	char* pt = ctime(&curtime);
	//char* pt = "hello world!";
	//写入磁盘文件
	int fd = open("/home/djh/linux/file.txt",O_CREAT | O_WRONLY | O_APPEND,0664);
	write(fd,pt,strlen(pt)+1);
	close(fd);
}

int main()
{
	//创建子进程
	pid_t pid = fork();

	if(pid > 0)
	{
		//结束父进程
		exit(1);
	}
	else if(pid == 0)
	{
		//子进程创建会话  变成守护进程
		setsid();
		//改变工作目录
		chdir("/home/djh");//一般没用
		//重置文件掩码
		umask(0);
		//关闭文件描述符
		close(0);//写宏会好一点
		close(1);
		close(2);

		//执行核心操作
		/*
		//注册信号捕捉
		struct sigaction sig;
		sig.sa_flags = 0;
		sig.sa_handler = dowork;//处理信号的回调函数
		sigemptyset(&sig.sa_mask);
		sigaction(SIGALRM,&sig,NULL);
		//创建定时器（sleep()也可以）
		struct itimerval val;
		//第一次触发的时间
		val.it_value.tv_usec = 0;
		val.it_value.tv_sec = 3;//第三秒开始发信号
		//循环周期
		val.it_value.tv_usec = 0;
		val.it_value.tv_sec = 1;//后续每隔一秒发一次信号
		setitimer(ITIMER_REAL,&val,NULL);
		*/
		while(1)//保证子进程处于运行状态
		{
			sleep(3);
			dowork();
		}
		
	}
	return 0;
}
