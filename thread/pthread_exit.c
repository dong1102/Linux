#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>


/*
 *线程退出
 *	函数原型：void pthread_exit(void* retval);
 *		retval指针：必须指向全局/堆的数据；
 *作用：让此线程退出不影响其他线程
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
		if(i == 2)
		{
			//exit(1);//会影响主线程
			pthread_exit(NULL);
		}
	}
	//pthread_exit(NULL);

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
	
	//pthread_exit(NULL);//退出主线程，此行之后的代码就不会被执行
	int i = 1;
	sleep(2);
	while(i)
	{
		printf("parent i:%d\n",i++);
	}

	pthread_exit(NULL);
	return 0;
}
