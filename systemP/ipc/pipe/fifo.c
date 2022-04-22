#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>


// int mkfifo(const char *path,mode_t mode); //0644

void server(int readfd, int writefd)
{
	ssize_t n;
	char buf[1024];
	int fd;
	memset(buf,'\0',sizeof(buf));
	if((n = read(readfd,buf,sizeof(buf))) == 0){
		exit(1);
	}
	buf[n] = '\0';
	if ((fd = open(buf,O_RDONLY)) < 0){
		snprintf(buf + n, sizeof(buf) - n, " can not open\n");
		write(writefd,buf,strlen(buf));
		exit(1);
	}
	while((n = read(fd,buf,sizeof(buf))) > 0){
		write(writefd,buf,n);
	}
	
	close(fd);
}


void client(int readfd,int writefd)
{
	char buf[1024];
	memset(buf,'\0',sizeof(buf));
	fgets(buf,sizeof(buf),stdin);
	size_t n = strlen(buf);
	if(buf[n-1] == '\n'){
		n--;
	}
	write(writefd,buf,n);
	
	while((n = read(readfd,buf,sizeof(buf))) > 0){
		write(STDOUT_FILENO,buf,n);
	}

}

int main(int argc,char **argv)
{
	int readfd,writefd;
	pid_t childPid;
	if( (mkfifo("fifo1",0666)) && (errno != EEXIST) ){
		printf("can not create fifo1\n");
	}
	if( (mkfifo("fifo2",0666)) && (errno != EEXIST) ){
		unlink("fifo1");
		printf("can not create fifo2\n");
	}
	childPid = fork();
	if(childPid == 0){
		//子进程
		readfd = open("fifo1",O_RDONLY);//以只读方式打开fifo会阻塞到其他进程以写方式打开这个fifo
		writefd = open("fifo2",O_WRONLY);//以只写方式打开fifo会阻塞到其他进程以读方式打开这个fifo
		server(readfd,writefd);
		exit(0);
	}

	 if(childPid > 0)
	{
		printf("client...\n");
		writefd = open("fifo1",O_WRONLY);
		readfd = open("fifo2",O_RDONLY);
		client(readfd,writefd);
		waitpid(childPid,NULL,0);

		unlink("fifo1");
		unlink("fifo2");

		exit(0);
	}
}


