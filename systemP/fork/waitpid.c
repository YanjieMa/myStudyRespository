#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
// pid_t fork(void);
// pid_t wait(int *status);
// pid_t waitpid(pid_t pid,int *status,int options) option=WNOHANG
//	WIFEXITED(status)	-->	WEXITSTATUS(status)	得到子进程退出值
//	WIFSIGNALED(status)	-->	WTERMSIG(status)	得到子进程异常终止的信号编号

int main(int argc,char **argv)
{
	int i=0;
	int ret = 0;
	pid_t pid[5];
	for(i=0; i<5; i++){
		if((pid[i] = fork()) == 0){
			while(i<100){
				i++;
				sleep(i);
			}
			break;
		}
	}
	if(i != 5){
		return i;
	}
	int status;
	// >0 回收的子进程id  =0 非阻塞没有子进程结束 -1失败
	// >0 指定pid =0同组子进程 -1任意子进程 <-1 绝对值所在组进程
	//waitpid()返回-1说明没有可以回收的子进程
	while((ret = waitpid(-1,&status,WNOHANG)) != -1){
		if(ret > 0){
			if(WIFEXITED(status)){
				printf("child %d end,return %d\n",ret,WEXITSTATUS(status));
			}
			if(WIFSIGNALED(status)){
				printf("child %d end, return %d\n",ret,WTERMSIG(status));
			}
		}else{
			sleep(1);
		}
	}

	return 0;
}
