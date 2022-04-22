#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

// int link(const char *oldpath,const cha *newpath);
// int unlink(const char * path);

int main(int argc,char **argv)
{
	char buf[1024];
	ssize_t n;

	int fd1 = open(argv[1],O_RDONLY);
	int fd2 = open(argv[2],O_RDWR|O_TRUNC|O_CREAT,0644);

	struct stat sbuf;
	int ret = stat(argv[1],&sbuf);
	printf("file size:%d\n",sbuf.st_size);
	
	//ssize_t read(int fd,void *buf,size_t count);
	//	返回值 0:读到文件末尾  >0:读到的字节数  -1:失败，errno=EAGIN或者EWOULDBLOCK说明以非阻塞方式读，并且无数据
	//	count:缓冲区大小 
	//ssize_t write(int fd,const void *buf,size_t count);
	//	返回值  >0:成功写入的字节数 -1:失败
	//int lseek(int handler,long off_set,int fromwhere);
	//long tell(int handler);
	while((n = read(fd1,buf,sizeof(buf))) > 0){
		write(fd2,buf,n);
	}

	close(fd1);
	close(fd2);
	
	return 0;
}

int main2 (int argc,char **argv)
{
	int n;
	// FILE * fopen(char *pathname, *type);
	// 成功返回文件流指针，失败返回空指针NULL
	// type : r w a r+ w+ a+ b t
	FILE *fp1 = fopen(argv[1],"r");
	FILE *fp2 = fopen(argv[2],"w");
	//向文件流写的函数
	//int fprintf(FILE *stream,char *format, ...);	成功返回写入的字节数 失败返回负值
	//int fputs(char *string,FILE *stream);		返回0表示成功 非0失败
	//int fputc(int ch,FILE *stream);		成功返回ch,失败返回EOF
	//int fscanf(FILE *stream,char *format, ...);	错误返回EOF,否则成功
	//char fgets(char *string,int n,FILE *stream);	读取至多n-1个，字符串末尾加入空字符\0，成功返回string指针，失败返回空指针NULL
	//int fgetc(FILE *stream);			读错返回EOF，成功返回当前位置的一个字符
	//int fseek(FILE *stream,long off_set,int fromwhere);	返回0成功，非0失败。SEEK_SET SEEK_CUR SEEK_END
	//int fread(void *buf,int size,int count,FILE *stream);	读取count个字段，每个字段size个字节
	//int fwrite(void *buf,int size,int count,FILE *stream);
	//long ftell(FILE *stream);	返回文件位置
	//int fflush(FILE *stream);
	//int feof(FILE *stream);	判断是否到达文件结尾，到达返回非0值，未到达返回0
	while((n = fgetc(fp1)) != EOF){
		fputc(n,fp2);
	}
	// int fclose(FILE *stream)
	fclose(fp1);
	fclose(fp2);

	return 0;	
}
