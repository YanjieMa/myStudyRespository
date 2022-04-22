#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

typedef struct {
	char name[5];
	int age;
}people;
int main(int argc ,char ** argv)
{
	int i;
	char name;
	int age;
	//MAP_ANONYMOUS 匿名映射
	people * p_map =(people * ) mmap(NULL,sizeof(people) * 15,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);

	pid_t pid;
	pid = fork();
	if(pid == 0){
		sleep(2);
		for(i=0; i< 5; i++){
			printf("name:%s, age:%d\n",p_map[i].name,p_map[i].age);
		}
		strncpy(p_map[0].name,"qwer",5);
		p_map[0].age = 100;
		return 0;
	}else if(pid > 0){
		name = 'a';
		age = 20;
		for(i=0;i<5;i++){
			memcpy(p_map[i].name,&name,1);
			p_map[i].age = age;
			name++;
			age++;
		}
		sleep(5);
		printf("name:%s, age:%d\n",p_map[0].name,p_map[0].age);
		munmap(p_map,sizeof(people)*5);
	}
	return 0; 	

}
