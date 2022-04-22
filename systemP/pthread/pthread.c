#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>

typedef struct PEO{
	char name[1024];
	int age;
}people;

void *func(void *arg)
{
	people *peo = (people *)arg;

	printf("p:name:%s,age:%d\n",peo->name,peo->age);
	printf("p:pid=%d,tid=%lu\n",getpid(),pthread_self());
	
	return (void *)0;
}

void *func2(void * arg)
{
	people *mpeo = malloc(sizeof(people));
	//void *memcpy(void *des,const void *from,size_t n);	绝对复制n个字符，不论有没有\0

	//strcpy(char *des,char *from)	根据\0作为结束判断，会把\0拷贝，des空间不够内存会溢出

	//strncpy(char *des,char *from,size_t n) 拷贝n个字符，不保证des以\0结束；若from较小，des较大，填充\0
	
	//sprintf(char *des,const char *format, ...);	拷贝到\0结束，存在des空间不足时 内存泄漏问题

	//snprintf(char *des,size_t size,const char *format,...);	只会拷贝n-1个，自动补充最后的\0		
	
	strcpy(mpeo->name,"qwer");
	mpeo->age = 40;
	
	printf("p1:pid=%d,tid=%lu\n",getpid(),pthread_self());
	pthread_exit((void *)mpeo);
}

void *func3(void *arg)
{
	printf("p3:pid=%d,tid=%lu\n",getpid(),pthread_self());
	
	pthread_exit((void *)0);
}

int main(int argc,char **argv)
{
	pthread_t tid;

	pthread_attr_t attr;

	people ma;
	
	strncpy(ma.name,"kira",sizeof(ma)-1);
	//snprintf(ma.name,sizeof(ma),"kira");
	ma.age = 27;

	int ret = pthread_attr_init(&attr);

	ret = pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	
	ret = pthread_create(&tid,&attr,func,(void *)&ma);

	ret = pthread_attr_destroy(&attr);

	ret = pthread_join(tid,NULL);
	if(ret < 0){
		printf("pthread_join error:%s\n",strerror(ret));
	}
	
	printf("main:name:%s,age:%d\n pid=%d,tid=%lu\n",ma.name,ma.age,getpid(),pthread_self());
	

	pthread_t tid2;
	ret = pthread_create(&tid2,NULL,func2,NULL);
	
	people * retpeo;
	pthread_join(tid2,(void **)&retpeo);
	printf("main2:name:%s,age:%d\n",retpeo->name,retpeo->age);
	
	
	pthread_t tid3;
	pthread_create(&tid3,NULL,func3,NULL);
	pthread_detach(tid3);


	pthread_exit((void *)0);
}

