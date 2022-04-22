#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
//int set_init(sem_t *sem,int pshared, unsigned int value);
// sem_wait();
// sem_post();
//int sem_destroy(sem_t *sem);

sem_t black_num,product_num;
int queue[5];
void * product_func(void *arg)
{
	int i=0;
	int para = (int) arg;

	while(1){
		sem_wait(&black_num);//做一次--操作，到0时，阻塞
		queue[i] = (rand() % 10) + 1;
		sem_post(&product_num);
		printf("%d pthread product %d\n",para,queue[i]);
		i = (i+1) % 5;
		sleep(rand() % 2);
	}
	pthread_exit(NULL);
}

void *consume_func(void *arg)
{
	int i = 0;
	int para = (int) arg;
	while(1){
		sem_wait(&product_num);
		printf("%d thread consume %d\n",para,queue[i]);
		queue[i] = 0;
		sem_post(&black_num);
		i = (i+1) % 5;
		sleep(rand() % 3);
	}
	pthread_exit(NULL);
}


int main(int argc,char **argv)
{
	pthread_t pid,cid;

	sem_init(&black_num,0,5);//0:用于线程间同步，1:用于进程间同步
	sem_init(&product_num,0,0);

	pthread_create(&pid,NULL,product_func,(void *)1);
	pthread_create(&cid,NULL,consume_func,(void *)1);
	
	pthread_join(pid,NULL);
	pthread_join(cid,NULL);

	sem_destroy(&black_num);
	sem_destroy(&product_num);
	
	return 0;
	
}

