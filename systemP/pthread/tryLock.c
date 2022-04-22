#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>


pthread_mutex_t mutex;
int gVal=0;

void *func1(void *arg)
{
	if(pthread_mutex_trylock(&mutex) != 0 ){
		gVal = 1;
		pthread_exit((void *) 0);
	}
	int i=0;
	gVal = 0;

	while(i<3){
		if(gVal){
			break;
		}
		printf("hellow\n");
		i++;
		sleep(1);
	}
	pthread_mutex_unlock(&mutex);
	pthread_exit((void*)1);
}

void *func2(void *arg)
{
	if(pthread_mutex_trylock(&mutex) != 0 ){
		gVal = 1;
		pthread_exit((void *) 0);
	}
	int i=0;
	gVal = 0;

	while(i<3){
		if(gVal){
			break;
		}
		printf("linux\n");
		i++;
		sleep(1);
	}
	pthread_mutex_unlock(&mutex);
	pthread_exit((void *)1);
}

void printf_hellow(void)
{
	pthread_t tid;
	pthread_create(&tid,NULL,func1,NULL);
}

void printf_linux(void)
{
	pthread_t tid;
	pthread_create(&tid,NULL,func2,NULL);
}


int main(int argc,char **argv)
{
	int flag;
	pthread_mutexattr_t attr;
	int ret = pthread_mutex_init(&mutex,&attr);
	if(ret < 0){
		printf("mutex init fail,mes:%s\n",strerror(ret));
		return 0;
	}
	while(1){
		scanf("%d",&flag);
		getchar();

		switch(flag){
			case 1:
				printf("start 1\n");
				printf_hellow();
				break;
			case 2:
				printf("start 2\n");
				printf_linux();
				break;
			defaule:
				break;
		}

	}

	pthread_mutex_destroy(&mutex);

	pthread_exit(0);
}

