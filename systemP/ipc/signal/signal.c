#include <signal.h>
#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

// int kill(pid_t pid,int signum);
// unsigned int alarm(unsigned int seconds);
// int setitimer(int which, const struct itimerval *new_value,const struct itimerval *old_value);
//	which:ITIMER_REAL ITIMER_VIRTUAL ITIMER_PROF
/*	struct itimerval{
		struct timeval{
			time_t tv_sev;
			suseconds_t tv_usec;	
		}it_interval;
		struct timecal{
			time_t tv_sec;
			suseconds_t tv_usec;
		}it_value;
	};
*/
void sigRot(int signum)
{
	switch(signum){
		case SIGHUP:
			printf("get SIGHUP\n");
			break;
		case SIGINT:
			printf("get SIGINT\n");
			break;
		case SIGQUIT:
			printf("get SIGQUIT\n");
			break;
		case SIGALRM:
			printf("get AIGALRM\n");
			break;
		default:
			break;
	}

	return ;
}

int main(int argc, char **argv)
{
	printf("process id is %d\n",getpid());

	//失败返回 SIGERR
	signal( SIGALRM,sigRot);
	
	struct itimerval timer,oldtimer;
	timer.it_value.tv_sec = 2;
	timer.it_value.tv_usec = 0;
	timer.it_interval.tv_sec = 4;
	timer.it_interval.tv_usec = 0;
	// ITIMER_REAL ITIMER_VIRTUAL ITIMER_PROF
	setitimer(ITIMER_REAL,&timer,&oldtimer);
	while(1){
		sleep(5);
		//kill(getpid(),SIGALRM); pid>0 pid=0 pid=-1 pid <-1
		//raise(SIGALRM);
		//alarm(1);
	}
	
	return 0;
}
