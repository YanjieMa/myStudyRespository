#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>

typedef struct{
	char name[5];
	int age;
}people;

int main(int argc , char **argv)
{

	int pagesize = sysconf(_SC_PAGESIZE);
	printf("page size is %d\n",pagesize);

	int fd = open(argv[1],O_CREAT|O_RDWR|O_TRUNC,0644);

	ftruncate(fd,pagesize*2 - 100);

	people *p_map = (people *)mmap(NULL,pagesize*3,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	close(fd);
	int i;
	for(i=1; i< 10; i++){
		(*(p_map + pagesize/sizeof(people)*i - 2)).age = 10;
		printf("access page %d over\n",i);
		(*(p_map + pagesize/sizeof(people)*i - 1)).age = 10;
		printf("access page %d edge over\n",i);
		(*(p_map + pagesize/sizeof(people)*i )).age = 10;
		printf("access page %d over\n",i+1);
	}
	munmap(p_map,pagesize*3);
}

