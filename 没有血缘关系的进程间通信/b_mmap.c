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
 *
 */
//共享内存在父子进程间通信
int main()
{
	int fd = open("temp",O_RDWR | O_CREAT,0664);
	ftruncate(fd,4096);//给磁盘文件扩展空间
        int len = lseek(fd,0,SEEK_END);//求文件大小
	
	void* ptr =  mmap(NULL,len,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
	if(ptr == MAP_FAILED)
	{
		perror("mmap error");
		exit(-1);
	}
	
	while(1)
	{
		sleep(1);
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
