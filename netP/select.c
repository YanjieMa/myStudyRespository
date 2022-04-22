#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_ADDR 9527

int select(int nfds,fd_set *readfds,fd_set *writefds,fd_set *errorfds,struct timeval *timeout);



int main()
{
	int i,n;
	char read_buf[1024];
	char str[1024];
	struct sockaddr_in server_addr,client_addr;
	socklen_t client_addr_len;
	int client[FD_SETSIZE];
	for(i=0;i<FD_SETSIZE;i++){
		client[i] = -1;
	}
	int listenfd = socket(AF_INET,SOCK_STREAM,0);
	
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(SERVER_ADDR);
	
	bind(listenfd,(struct sockaddr *)&server_addr,sizeof(server_addr));

	listen(listenfd,20);
	int sockfd;	
	int maxi = -1;
	int maxfd = listenfd;
	fd_set all_set,read_set;
	FD_ZERO(&all_set);
	FD_SET(listenfd,&all_set);
	
	while(1){
		read_set = all_set;

		int nready = select(maxfd + 1,&read_set,NULL,NULL,NULL);	
		if(nready < 0){
			perror("select error");
			return -1;
		}
		if(FD_ISSET(listenfd,&read_set)){
			client_addr_len = sizeof(client_addr);
			int connfd = accept(listenfd,(struct sockaddr *)&client_addr,&client_addr_len);
			printf("receive connect from %s:%d\n",inet_ntop(AF_INET,&client_addr.sin_addr,str,sizeof(str)),ntohs(client_addr.sin_port));
			for(i=0;i<FD_SETSIZE;i++){
				if(client[i] < 0){
					client[i] = connfd;
					break;
				}
			}
			if(i == FD_SETSIZE){
				fputs("too many client connect\n",stderr);
				exit(-2);
			}
			FD_SET(connfd,&all_set);
			if(connfd>maxfd)
				maxfd = connfd;
			if(i>maxi)
				maxi = i;
			if(--nready == 0)
				continue;
		}
		for(i = 0; i <= maxi; i++){
			printf("sockfd = %d\n",client[i]);
			if((sockfd = client[i]) < 0)
				continue;
			if(FD_ISSET(client[i],&read_set)){
				while((n = read(client[i],read_buf,sizeof(read_buf))) > 0){
					int j;
					for(j=0;j<n;j++){
						read_buf[j] = toupper(read_buf[j]);
					}
					write(client[i],read_buf,n);
				}
				if(n == 0){
					printf("client closed\n");
					close(client[i]);
					FD_CLR(client[i],&all_set);
					client[i] = -1;
				}else{
					perror("read error");
					exit(-3);
				}
#if 0
				if((n = read(client[i],read_buf,sizeof(read_buf))) == 0){
					printf("client closed\n");
					close(client[i]);
					FD_CLR(client[i],&read_set);
					client[i] = -1;
				}else if(n > 0){
					int j;
					for(j=0;j<n;j++){
						read_buf[j] = toupper(read_buf[j]);
					}
					write(client[i],read_buf,n);
				}else{
					perror("read error");
				}
#endif			
				if(--nready == 0)
					break;				
			}
		}	
	}	
	close(listenfd);
	return 0;
}
