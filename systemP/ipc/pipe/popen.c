#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//FILE *popen(char *cmd,*type);
int main(int argc, char ** argv)
{
	char buf[1024];
	char comd[1024];

	fgets(buf,sizeof(buf),stdin);
	size_t n = strlen(buf);
	
	if(buf[n-1] == '\n'){
		n--;
	}
	snprintf(comd,sizeof(comd),"cat %s",buf);
	FILE *fp = popen(comd,"r");
	while(fgets(buf,sizeof(buf),fp) > 0){
		fputs(buf,stdout);
	}
	pclose(fp);
	exit(0);


}
