#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/types.h>
typedef struct PEO{
	char name[10];
	int age;
}people;

int main(int argc, char ** argv)
{
	int i;
	int fd = open(argv[1],O_CREAT|O_RDWR,0644);
	people * p_map = mmap(NULL,sizeof(people)*10,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	for(i=0;i<10;i++){
		printf("name:%s, age:%d\n",p_map[i].name,p_map[i].age);
		
	}
	close(fd);
	munmap(p_map,sizeof(people)*10);

	return 0;
}
