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


pthread_mutex_t mutex;//定义一把互斥锁

void *func(void *arg)
{
	people *peo = (people *)arg;

	printf("p:name:%s,age:%d\n",peo->name,peo->age);
	printf("p:pid=%d,tid=%lu\n",getpid(),pthread_self());
	
	people *rPeo = malloc(sizeof(people));

	snprintf(rPeo->name,sizeof(rPeo->name),"xiaoma");
	rPeo->age = 30;
	while(1){
		pthread_mutex_lock(&mutex);
		printf("hellow ");
		sleep(rand()%3);
		printf("linux\n");
		pthread_mutex_unlock(&mutex);
		sleep(rand() % 3);
	}
	pthread_exit((void *)rPeo);
}


int main(int argc,char **argv)
{
	pthread_t tid;
	srand(time(NULL));
	pthread_attr_t attr;

	people ma;
	
	strncpy(ma.name,"kira",sizeof(ma)-1);
	ma.age = 27;

	int ret = pthread_attr_init(&attr);

	//ret = pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	
	ret = pthread_create(&tid,&attr,func,(void *)&ma);

	ret = pthread_attr_destroy(&attr);

	pthread_mutex_init(&mutex,NULL);

	printf("main:name:%s,age:%d\n pid=%d,tid=%lu\n",ma.name,ma.age,getpid(),pthread_self());
	while(1){
		pthread_mutex_lock(&mutex);//加锁
		printf("HELLOW ");
		sleep(rand() % 3);
		printf("LINUX\n");
		pthread_mutex_unlock(&mutex);//解锁
		sleep(rand() % 3);
	}

	people *rVal;
	ret = pthread_join(tid,(void **)&rVal);
	if(ret < 0){
		printf("pthread_join error:%s\n",strerror(ret));
	}
	printf("main:rVal:name:%s,age:%d\n",rVal->name,rVal->age,getpid(),pthread_self());

	pthread_mutex_destroy(&mutex);
	pthread_exit((void *)0);
	
}

