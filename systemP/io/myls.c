#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

//DIR *opendir(char *name);
//struct dirent *readdir(DIR *dp);
//int closedir(DIR *dp);


int main(int argc,char **argv)
{
	DIR *dp = opendir(argv[1]);
	/*struct dirent{
		int inode;
		char d_name[256];
	}*/
	struct dirent *sdp;
	while((sdp = readdir(dp)) != NULL){
		printf("%s\t",sdp->d_name);
	}
	printf("\n");
	closedir(dp);
	return 0;
}

