#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

//int dup(int oldfd);
//int dup2(int oldfd,mewfd);
//int newfd fcntl(int fd,F_DUPFD,0);

int main(int argc,char **argv)
{
	int fd = open(argv[1],O_RDWR|O_TRUNC|O_CREAT,0644);
	
	int ret = dup2(fd,STDOUT_FILENO);
	if(ret < 0){
		perror("dup2 error\n");
	}
	printf("qwer\n");
	
	ret = dup2(STDIN_FILENO,fd);
	if(ret < 0){
		perror("error msg\n");
	}
	write(fd,"qaz\n",4);
	close(fd);
	return 0;
}

