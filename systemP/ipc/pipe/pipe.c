#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

//int pipe(int fd[2]);
//读管道：管道有数据，返回实际读到的字节数
//	  管道无数据，无写端，read返回0；有写端，read阻塞
//写管道：无读端，异常终止
//	  有读端，已满，阻塞等待；未满，返回实际写入的字节数
void client(int readfd,int writefd)
{
	ssize_t n;
	char buf[1024];
	//memset(buf,'\0',sizeof(buf)),
	//bzero(buf,sizeof(buf));
	fgets(buf,sizeof(buf),stdin);
	size_t len = strlen(buf);
	if(buf[len-1] == '\n'){
		len--;
	}
	write(writefd,buf,len);
	while((n = read(readfd,buf,sizeof(buf))) > 0){ //阻塞读
		write(STDOUT_FILENO,buf,n);
	}

}

void server(int readfd,int writefd)
{
	int fd;
	ssize_t n;
	char buf[1024+1];
	memset(buf,'\0',sizeof(buf));
	if((n = read(readfd,buf,sizeof(buf))) == 0){
		printf("fail to read path name");
		exit(1);
	}
	buf[n] = '\0';
	if((fd = open(buf,O_RDONLY)) < 0){//出错
		snprintf(buf+n,sizeof(buf)-n," can not open\n");
		n = strlen(buf);
		write(writefd,buf,n);
	}else{
		while((n = read(fd,buf,sizeof(buf))) > 0){
			write(writefd,buf,n);
		}
		close(fd);
	}
}

int main(int argc,char **argv)
{
	int pipe1[2];
	int pipe2[2];

	pid_t childPid;
	
	pipe(pipe1);
	pipe(pipe2);
	
	if((childPid = fork()) == 0){
		//子进程
		close(pipe1[1]);
		close(pipe2[0]);
		server(pipe1[0],pipe2[1]);
		exit(0);
	}else if(childPid > 0){	
		close(pipe1[0]);
		close(pipe2[1]);
		client(pipe2[0],pipe1[1]);
		// ret = waitpid(pid,&status,WNOHANG)	
		// 非阻塞回收，成功返回回收的pid，失败返回0。
		waitpid(childPid,NULL,0);
		exit(0);
	}
}
