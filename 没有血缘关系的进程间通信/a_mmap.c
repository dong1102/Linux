#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/wait.h>

/*
 *没有血缘关系的进程通过共享内存通信：
 *    不能使用匿名的映射方式；
 *    只能借助磁盘文件创建映射区；
 *    磁盘文件只是中间桥梁，让两个进程的映射区指向同一块物理内存，操作的数据都在内存上
 */
//使用共享内存在无血缘关系的进程间通信
int main()
{
	int fd = open("temp",O_RDWR | O_CREAT,0664);
	ftruncate(fd,4096);//给磁盘文件扩展空间
	int len = lseek(fd,0,SEEK_END);//求文件大小

	//创建有名共享内存
	void* ptr =  mmap(NULL,len,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
	if(ptr == MAP_FAILED)
	{
		perror("mmap error");
		exit(-1);
	}
	while(1)
	{
		strcpy((char*)ptr,"这是无血缘关系进程间的共享内存！\n");
		sleep(2);
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
