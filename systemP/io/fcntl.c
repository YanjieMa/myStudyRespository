#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc,char **argv)
{
	// int open(const char *pathname,int flags);
	// int open(const char *pathname,int flags, mode_t mode);
	// 成功：返回文件描述符fd	失败：返回-1 设置errno
	// flags:O_RDONLY O_WRONLY O_RDWR O_TRUNC O_EXCL O_NONBLOCK O_CREATE O_APPEND
	// mode:文件权限=mode & ~mask	such as:0644
	// int close(int fd);
	int fd = open(argv[1],O_RDWR|O_CREAT,0644);
	// int flags = fcntl(int fd,F_GETFL);	
	int newfd = fcntl(fd,F_DUPFD,0);
	
	int flag = fcntl(fd,F_GETFL);
	flag = flag | O_NONBLOCK;
	
	// fcntl(intfd, F_SETFL, int flags);
	fcntl(fd,F_SETFL,flag);

	return 0;
}

