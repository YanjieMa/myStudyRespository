#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>

//int socket(int domain,int type,int protocol);
//	domain: AF_INET AF_INET6 AF_UNIX
//	type: SOCK_STREAM SOCK_DGRAM
//int bind(int sockfd,const struct sockaddr *addr,socklen_t addrlen);
//int listen(int sockfd,int backlog);
//const char *inet_ntop(int af,const void *, char *dst,socklen_t size);

#define SERVER_PORT 9527

struct thread_info{
	int connfd;
	struct sockaddr_in addr;
};

void *do_work(void *arg)
{
	int j;
	char str[256];
	char read_buf[1024];
	struct thread_info *info = (struct thread_info *)arg;
	printf("thread:pid=%d,tid=%lu\n",getpid(),pthread_self());
	
	while(1){
		int n = read(info->connfd,read_buf,sizeof(read_buf));
		if(n==0){
			printf("client closed\n");
			break;
		}else if(n>0){
			printf("recive from %s:%d\n",inet_ntop(AF_INET,&info->addr.sin_addr,str,sizeof(str)),ntohs(info->addr.sin_port));
			for(j=0;j<n;j++){
				read_buf[j] = toupper(read_buf[j]);
			}
			if(!strcmp(read_buf,"EXIT\n")){
				break;
			}
			write(info->connfd,read_buf,n);
		}
		
	}
	close(info->connfd);
	pthread_exit((void *)0);

}


int main(int argc,char **argv)
{
	int i=0;
	pthread_t tid;
	struct thread_info ts[256];
	struct sockaddr_in server_addr,client_addr;
	socklen_t client_addr_len;

	int listenfd = socket(AF_INET,SOCK_STREAM,0);	
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(SERVER_PORT);

	bind(listenfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
	
	listen(listenfd,20);
	char out_buf[1024];
	char *ready = "ready to accept client...\n";
	//memcpy(out_buf,ready,strlen(ready)+1);
	//strcpy(out_buf,ready);
	//sprintf(out_buf,"%s",ready);
	snprintf(out_buf,sizeof(out_buf),"%s",ready);
	write(STDOUT_FILENO,out_buf,strlen(out_buf));
	while(1){
		client_addr_len = sizeof(client_addr);
		int connfd = accept(listenfd,(struct sockaddr *)&client_addr,&client_addr_len);			
		if(connfd < 0){
			if(errno==EINTR) continue;
			perror("accept error");
			break;
		}
		ts[i].addr = client_addr;
		ts[i].connfd = connfd;
		pthread_create(&tid,NULL,do_work,(void *)&ts[i]);	
		i++;
		printf("main:pid=%d,tid=%lu\n",getpid(),pthread_self());
		pthread_detach(tid);

	}
	
	return 0;
}
