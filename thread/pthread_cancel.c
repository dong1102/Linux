#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>


/*
 *线程取消
 *	函数原型：void pthread_cancel(pthread_t pthid);
 *		pthid：对应子线程的线程id；
 *	作用：杀死对应线程id的子线程。
 *	注意事项：
 *		并不一定调用此函数就一定能杀死子线程；
 *		将要被杀死的子线程的处理函数内部必须有一个取消点，即系统调用（间接调用也算，比如printf函数），才能成功杀死此子线程。
 *		pthread_testcancle()函数：是一个系统调用，作为一个取消点存在，没有实际意义。
 *		如果想让主线调用pthread_cancle杀死子线程，但是不知道子线程处理函数中没有使用系统调用，则子线程处理函数中调用pthread_testcancle()即可；
 *
 */


//子线程的回调函数
void* show(void* arg)
{
	int i = 0;
	while(i < 5)
	{
		if(i == 3)
		{
			printf("将要被杀死了,child_id=%lu,i=%d\n",pthread_self(),i);
		}
		i++;
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
	
	pthread_cancel(pthid);//杀死子线程
	printf("parent thread id:%lu\n",pthread_self());//打印主线程id
	
	int i = 0;
	while(i < 10)
	{
		printf("parent i:%d\n",i++);
	}

	pthread_exit(NULL);
	return 0;
}
