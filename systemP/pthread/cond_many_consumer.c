#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>

struct node{
	int num;
	struct node *next;
};

pthread_cond_t has_product;
pthread_mutex_t lock;

struct node *head;

void *product(void *arg)
{
	int para =  (int) arg;
	struct node *msg;

	while(1){
		msg = malloc(sizeof(struct node));
		msg->num = rand() % 100 + 1;
		printf("product%d  ====>   %d\n",para,msg->num);
		pthread_mutex_lock(&lock);
		msg->next = head;
		head = msg;
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&has_product);
		sleep(rand()%5);
	}
	pthread_exit(NULL);
}
void *consumer(void *arg)
{
	int para = (int) arg;
	struct node*msg;

	while(1){
		pthread_mutex_lock(&lock);
		while(head == NULL){
			pthread_cond_wait(&has_product,&lock);
		}
		msg = head;
		head = head->next;
		pthread_mutex_unlock(&lock);
		printf("consumer%d ==> %d\n",para,msg->num);
		free(msg);
		sleep(rand()%5);
	}
	pthread_exit(NULL);
}

int main(int argc,char **argv)
{
	pthread_t pro_id[3],con_id[3];
	
	pthread_cond_init(&has_product,NULL);
	pthread_mutex_init(&lock,NULL);

	srand(time(NULL));
	
	pthread_create(&pro_id[0],NULL,product,(void *)1);
	pthread_create(&con_id[0],NULL,consumer,(void *)1);
	pthread_create(&pro_id[1],NULL,product,(void *)2);
	pthread_create(&con_id[1],NULL,consumer,(void *)2);
	pthread_create(&pro_id[2],NULL,product,(void *)3);
	pthread_create(&con_id[2],NULL,consumer,(void *)3);

	pthread_join(pro_id[0],NULL);
	pthread_join(con_id[0],NULL);
	pthread_join(pro_id[1],NULL);
	pthread_join(pro_id[2],NULL);
	pthread_join(con_id[1],NULL);
	pthread_join(con_id[2],NULL);
	
	return 0;
		
}

