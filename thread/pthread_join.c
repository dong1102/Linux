#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>


/*
 *阻塞等待子线程退出：pthread_join
 *	函数原型：int pthread_join(pthread_t pthid,void** retval);
 *		pthid:要回收的子线程id；
 *		retval二级指针：读取线程退出时携带的状态信息；必须指向全局或堆上的内存
 *			是一个传出参数，指向的内存和pthread_exit参数指向同一块内存地址。
 *作用：子线程和子进程一样，都无法回收自己的pcb
 *
 */


//子线程的回调函数
void* show(void* arg)
{
	printf("child thread id:%lu\n",pthread_self());
	int i = 0;
	while(i < 5)
	{
		printf("child i:%d\n",i++);
	}

	return NULL;
}

int main()
{
	pthread_t pthid;//线程id
	int ret = pthread_create(&pthid,NULL,show,NULL);//创建线程
	if(ret != 0)
	{
		printf("error num:%d,%s\n",ret,strerror(ret));//打印错误信息
	}

	printf("parent thread id:%lu\n",pthread_self());//打印主线程id
	
	pthread_join(pthid,NULL);//如果想获取子线程的退出信息，则定义一个指针传入NULL的位置。
	int i = 0;
	while(i < 10)
	{
		printf("parent i:%d\n",i++);
	}

	//pthread_exit(NULL);
	return 0;
}
