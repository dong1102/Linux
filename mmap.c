#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/wait.h>

/*
 *共享内存/内存映射：
 *    共享内存就是多个进程共享同一块物理内存；将这块物理内存分别映射到自己的虚拟空间地址上。
 *
 *    创建共享内存/内存映射区：
 *        mmap———创建内存映射
 *        作用：将磁盘文件映射到内存，用户通过修改内存就能修改磁盘文件。
 *        mmap既可以单纯的操作文件，也可以进行进程间通信。
 *        函数原型：void* mmap ( void * addr , size_t len , int prot , int flags , int fd , off_t offset ) 
 *        参数：
 *            addr是映射区首地址，传NULL；
 *            len是映射到调用进程地址空间的字节数；
 *            prot 参数指定共享内存的访问权限；
 *            flags是标志位参数，由以下几个常值指定：MAP_SHARED , MAP_PRIVATE , MAP_FIXED，其中，MAP_SHARED , MAP_PRIVATE必选其一；
 *            fd是打开的文件描述符，若没有文件则为-1；
 *            offset参数一般设为0，表示从文件头开始映射。
 *        问题：
 *            1、如果对mmap的返回值（ptr）做++操作，munmap（释放mmap）是否能够成功？
 *            不能
 *
 */
//共享内存在父子进程间通信
int main()
{
	int len = 4096;//必须是4096的整数倍
	//创建匿名共享内存
	void* ptr =  mmap(NULL,len,PROT_READ | PROT_WRITE,MAP_SHARED | MAP_ANON,-1,0);
	if(ptr == MAP_FAILED)
	{
		perror("mmap error");
		exit(-1);
	}
	
	//创建子进程
	pid_t pid = fork();
	if(pid < 0)
	{
		perror("fork error");
		exit(-1);
	}
	//父进程在共享内存中写数据
	if(pid > 0)
	{
		strcpy((char*)ptr,"这是匿名的共享内存！\n");
		wait(NULL);//进程回收
	}
	//子进程读
	if(pid == 0)
	{
		printf("%s\n",(char*)ptr);
	}

	//释放共享内存
	int ret = munmap(ptr,len);
	if(ret == -1)
	{
		perror("munmap error\n");
		exit(-1);
	}

	return 0;
}

