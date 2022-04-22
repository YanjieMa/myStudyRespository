#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>

typedef struct PEOPLE{
	char name[10];
	int age;
}people;

int main(int argc, char **argv)
{
	int i = 0;
	int fd = open(argv[1],O_CREAT|O_RDWR|O_TRUNC,0755);
	lseek(fd,sizeof(people)*15,SEEK_SET);
	write(fd,"",1);
//	ftruncate(fd,seziof(people)*5);
	
	//void *mmap(void *addr,size_t len,int port,int flags,int fd,off_t offset)  prot:PROT_READ PROT_WRITE PROT_EXEC PROT_NONE flags:MAP_SHARED MAP_PRIVATE MAP_ANONYMOUS 匿名映射
	people *p_map =(people *) mmap(NULL,sizeof(people)*10,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	close(fd);

	char name = 'a';
	int age = 10;
	for(i=0; i< 10; i++){
		memcpy(p_map[i].name,&name,2);
		p_map[i].age = age;
		name++;
		age++;
	}
	printf("read over\n");
	sleep(10);
	munmap(p_map,sizeof(people)*10);
	printf("munmap ok \n");
}
