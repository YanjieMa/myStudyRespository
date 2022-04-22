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
	struct node *msg;

	while(1){
		msg = malloc(sizeof(struct node));
		msg->num = rand() % 100 + 1;
		printf("product====> %d\n",msg->num);
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
	struct node*msg;

	while(1){
		pthread_mutex_lock(&lock);
		if(head == NULL){
			pthread_cond_wait(&has_product,&lock);
		}
		msg = head;
		head = head->next;
		pthread_mutex_unlock(&lock);
		printf("consumer ==> %d\n",msg->num);
		free(msg);
		sleep(rand()%5);
	}
	pthread_exit(NULL);
}

int main(int argc,char **argv)
{
	pthread_t pro_id,con_id;
	
	pthread_cond_init(&has_product,NULL);
	pthread_mutex_init(&lock,NULL);

	srand(time(NULL));
	
	pthread_create(&pro_id,NULL,product,NULL);
	pthread_create(&con_id,NULL,consumer,NULL);

	pthread_join(pro_id,NULL);
	pthread_join(con_id,NULL);
	
	return 0;
		
}

