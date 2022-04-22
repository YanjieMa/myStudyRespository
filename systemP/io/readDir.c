#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/stat.h>

void read_dir(char *name,void (*func)(char *))
{
	DIR *dp = opendir(name);
	/*struct dirent {
		int inode;
		char d_name[256];
	}*/
	struct dirent *sdp;
	
	while((sdp = readdir(dp)) != NULL){
		if(strcmp(sdp->d_name,".")==0 || strcmp(sdp->d_name,"..")==0){
			continue;
		}
		char path[256];
		sprintf(path,"%s/%s",name,sdp->d_name);
		
		(*func)(path);
	}	
	closedir(dp);
}

void isFile(char *name)
{
	int ret = 0;
	struct stat st;
	//int stat(const char *path,struct stat *buf);	
	//	文件大小：buf->st_size	文件类型：buf->st_mode
	ret = stat(name,&st);
	
	if(S_ISDIR(st.st_mode)){
		read_dir(name,isFile);
	}else{
		printf("%10s\t\t%ld\n",name,st.st_size);
	}
	return ;
}

int main(int argc,char **argv)
{
	if(argc == 1){
		isFile(".");
	}else{
		isFile(argv[1]);
	}


	return 0;
}

