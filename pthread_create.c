#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>


/*
 *线程：
 *	线程就是进程的一条执行路径，每一个进程都有一条线程，称之为主线程。
 *	进程在创建线程之后，地址空间没有发生改变，但自己退化成一条线程（主线程）；
 *	创建出的子线程和主线程公用地址空间，但是每个线程都有自己独立的pcb，子线程的pcb是从主线程拷贝而来；
 *
 *	主线程与子线程共享的：
 *		.text段、.bass段、.data段、堆、动态库加载区、环境变量、命令行参数；
 *	不共享的：栈
 *		地址空间的栈区会被n个线程平均分成n份；
 *		
 *在Linux系统下：
 *	线程就是轻量级的进程；
 *	在Linux内核看来，线程就是进程；
 *		因为linux系统早期是没有线程概念的，只有pcb表示的进程，而在后来发展中，程序员用进程的方式封装了线程，所以每个线程都有独立的pcb，所以在Linux内核中是分不清进程和线程的（一律当进程处理）；
 *
 *创建线程：
 *	函数原型：int pthread_create(pthread_t* thread,const pthread_attr_t* attr,void*（*start_routine)(void*),void* arg);
 *	引用头文件：#include<pthread.h>
 *	参数：
 *		thread：传出参数，线程创建成功之后，会被设置一个合适的值；
 *		attr：默认传NULL；
 *		start_routine：函数指针，回调函数（指向子线程的处理函数）；
 *		arg：处理函数的参数
 *	
 */

//创建五个线程，打印出他们是第几个被创建出来的

//子线程的回调函数
void* show(void* arg)
{
	//取参数
	//int num = *((int*)arg);//取得是地址
	int num = (int)arg;//取得是值
	printf("第%d个创建的子线程:%lu\n",num,pthread_self());

	return NULL;
}

int main()
{
	int n = 1;
	pthread_t pthid[5];//线程id
	while (n < 6)
	{
		//第四个参数是给回调函数传的参数，传的是地址；在这个地方传地址会出现问题，因为五个进程的地址都指向同一块空间
		//pthread_create(&pthid[n],NULL,show,(void*)&n);//创建线程
		//给第四个参数传值
		pthread_create(&pthid[n],NULL,show,(void*)n);//创建线程
		n++;
	}
	printf("parent thread id:%lu\n",pthread_self());//打印主线程id
	
	sleep(3);
	return 0;
}
