#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>

pthread_rwlock_t rwlock;
int val = 0;

void *func_read(void * arg)
{
	int rev = (int)arg;
	while(1){
		pthread_rwlock_rdlock(&rwlock);
		printf("read thread=%lu,val=%d\n",pthread_self(),val);
		pthread_rwlock_unlock(&rwlock);
		sleep(1);
	}
	pthread_exit(NULL);
}

void *func_write(void *arg)
{
	int rev = (int )arg;
	while(1){
		sleep(1);
		pthread_rwlock_wrlock(&rwlock);
		val++;
		printf("write thread=%lu,val=%d\n",pthread_self(),val);
		pthread_rwlock_unlock(&rwlock);
		sleep(6);
	}
	return NULL;
}
int main(int argc,char **argv)
{
	int i;
	pthread_t tid[8];
	pthread_rwlockattr_t rwlockattr;

	pthread_rwlock_init(&rwlock,&rwlockattr);	
	
	for(i=0;i<3;i++){
		pthread_create(&tid[i],NULL,func_write,(void*)i);
	}
	for(i=3;i<8;i++){
		pthread_create(&tid[i],NULL,func_read,(void*) i);
	}
	for(i=0;i<8;i++){
		pthread_join(tid[i],NULL);
	}

	pthread_rwlock_destroy(&rwlock);
}

