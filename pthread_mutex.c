#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

//线程同步、互斥锁详情：https://blog.csdn.net/djh971102/article/details/99607809 

#define MAX 10000
int num ;
//定义锁
pthread_mutex_t mutex;

void* fun1()
{
	int i = 0;
	for(;i < MAX;i++)
	{
		pthread_mutex_lock(&mutex);//加锁
		num++;
		printf("A-->num=%d\n",num);
		pthread_mutex_unlock(&mutex);//解锁
		usleep(10);
	}
}

void* fun2()
{
	int i = 0;
	for(;i < MAX;i++)
	{
		pthread_mutex_lock(&mutex);//加锁
		num++;
		printf("B-->num=%d\n",num);
		pthread_mutex_unlock(&mutex);//解锁
		usleep(10);
	}
}

int main()
{
	pthread_t pthid1,pthid2;
	//初始化锁
	pthread_mutex_init(&mutex,NULL);

	pthread_create(&pthid1,NULL,fun1,NULL);
	pthread_create(&pthid2,NULL,fun2,NULL);

	pthread_join(pthid1,NULL);
	pthread_join(pthid2,NULL);
	
	printf("AB-->num=%d\n",num);
	//销毁锁
	pthread_mutex_destroy(&mutex);

	return 0;
}
