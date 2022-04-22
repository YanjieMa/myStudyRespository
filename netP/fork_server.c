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
void do_child(int signum)
{
	pid_t r_pid;
	while((r_pid = waitpid(0,NULL,WNOHANG)) > 0){
		printf("receive %d process end\n",r_pid);
	}
}

int main(int argc,char **argv)
{
	int i;
	char read_buf[1024];
	char str[256];
	struct sockaddr_in client_addr,server_addr;
	socklen_t client_addr_len;

	struct sigaction act;

	act.sa_handler = do_child;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);

	sigaction(SIGCHLD,&act,NULL);
	

	int listenfd = socket(AF_INET,SOCK_STREAM,0);
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(SERVER_PORT);

	bind(listenfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
	
	listen(listenfd,5);
	
	printf("begin to listen client ...\n");
	int connfd;
	while(1){
		client_addr_len= sizeof(client_addr);
		connfd = accept(listenfd,(struct sockaddr *)&client_addr,&client_addr_len);
		if(connfd < 0){
			if(errno == EINTR) continue;
			printf("errno = %d, errstr=%s\n",errno,strerror(errno));
			break;
		}
		printf("connfd = %d\n",connfd);
		pid_t pid = fork();

		if(pid == 0){
			close(listenfd);
			while(1){
				int n = read(connfd,read_buf,sizeof(read_buf));
				if(n==0){
					printf("client has closed\n");
					break;
				}else if(n<0){
					char path[256];
					sprintf(path,"n=%d,errno = %d, errstr=%s\n",n,errno,strerror(errno));
					write(STDOUT_FILENO,path,strlen(path));
					break;
				}
				printf("receive from %s:%d\n",inet_ntop(AF_INET,&client_addr.sin_addr,str,sizeof(str)),ntohs(client_addr.sin_port));
				for(i=0;i<n;i++){
					read_buf[i] = toupper(read_buf[i]);
				}
				write(connfd,read_buf,n);
				read_buf[n] = '\0';
				char exit[256];
				memcpy(exit,"EXIT\n",5);
				write(STDOUT_FILENO,read_buf,n);
				write(STDOUT_FILENO,exit,256);
				
				if(!(strcmp(read_buf,exit))){
					write(STDOUT_FILENO,"exit",5);
					break;
				}
			}
			close(connfd);
			exit(0);
		}else if(pid > 0){
			close(connfd);
		}else{
			perror("fork error");
		}
	

	}//end while
	close(listenfd);

	return 0;
}
