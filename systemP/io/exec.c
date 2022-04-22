#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

//int execlp(const char *file,const char *arg, ...);
//int exexl(const char *path,const char *arg, ...);
//最后要加上NULL作为结束标志
int main(int argc,char **argv)
{
	int fd = open(argv[1],O_RDWR|O_TRUNC|O_CREAT,0644);
	
	dup2(fd,STDOUT_FILENO);

	execlp("ps","ps","aux",NULL);
	
	close(fd);

	return 0;

}
