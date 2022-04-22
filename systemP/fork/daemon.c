#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc,char **argv)
{
	//1.创建子进程，父进程终止
	int pid = fork();
	if(pid > 0){
		exit(0);
	}
	//2.子进程创建会话
	int sid = setsid();

	//3.改变工作目录位置
	chdir("/home/admin/");
	
	//4.修改文件访问权限掩码
	umask(0022);

	//5.关闭文件描述符或者重定向文件描述符
	close(STDIN_FILENO);
	int fd = open("/dev/null",O_RDWR);
	dup2(fd,STDOUT_FILENO);
	dup2(fd,STDERR_FILENO);
	//int newfd = fcntl(fd,F_DUPFD,0);
	
	//最后实现业务逻辑
	while(1){
		sleep(1);
	}

}
