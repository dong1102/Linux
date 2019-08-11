#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>


/*
 *线程分离
 *	函数原型：void pthread_detach(pthread_t pthid);
 *		pthid：要和主线程分离的子线程id；
 *	作用：
 *		调用线程分离函数之后，子线程就可以自己回收自己的pcb；
 *		调用线程分离函数后就不需要调用pthread_join()函数了。
 *
 */


//子线程的回调函数
void* show(void* arg)
{
	printf("child thread id:%lu\n",pthread_self());
	int i = 0;
	while(i < 5)
	{
		printf("chile i:%d\n",i++);
	}
	pthread_exit(NULL);

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
	pthread_detach(pthid);//将子线程与主线程分离
	
	int i = 0;
	while(i < 10)
	{
		printf("parent i:%d\n",i++);
	}

	pthread_exit(NULL);
	return 0;
}
