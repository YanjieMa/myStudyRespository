#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/time.h>

void handfunc(int sig,siginfo_t *info,void *act)
{
	/* typedef siginfo{
		int si_signo;
		int si_errno;
		int si_code;
		//等等。。。。
		union sigval si_value;
	}siginfo */
	if(sig == 50){
		printf("catch SIGALRM\n");
		printf("para:%d\n",info->si_value.sival_int);
	}
}

int main(int argc ,char ** argv)
{
	/*struct sigaction{
		sighandler_t sa_handler;
		void (*sa_sigaction)(int, struct siginfo *,void *)
		sigest_t sa_mask;
		unsigned longsa_flags;
	}*/	
	struct sigaction newact,oldact;
	//newact.sa_handler = handfunc;
	newact.sa_sigaction = handfunc;
	newact.sa_flags =SA_SIGINFO;// SA_NODEFER | SA_RESETHAND | SA_SIGINFO;
	//信号集及函数
	sigemptyset(&newact.sa_mask);
	sigaddset(&newact.sa_mask,SIGQUIT);
	//sigfillset(&newact.sa_mask);
	//sigdelset(&newact.sa_mask,SIGQUIT);
	if(sigismember(&newact.sa_mask,SIGQUIT)){
		printf("sigaddset sucess\n");
	}
	/* typedef siginfo{
		int si_signo;
		int si_errno;
		int si_code;
		union sigval si_value;
	}siginfo */
	/* union sigval{
		int sival_int;
		void *sival_ptr;
	}*/
	union sigval mysigval;
	mysigval.sival_int = 30;	
	
	sigset_t sigmask,odmask;
	sigemptyset(&sigmask);
	sigaddset(&sigmask,50);
	//SIG_BLOCK SIG_UNBLOCK SIG_SETMASK

	sigprocmask(SIG_BLOCK,&sigmask,&odmask);
	sigaction(50,&newact,&oldact);
	sleep(1);
	sigqueue(getpid(),50,mysigval);
	sigset_t pendmask;
	sigpending(&pendmask);
	if(sigismember(&pendmask,50)){
		printf("50 bei zu se \n");
	}
	sigprocmask(SIG_SETMASK,&odmask,NULL);
	printf("qu xiao 50 zu se \n");
	while(1){
		sleep(2);
		sigqueue(getpid(),50,mysigval);
	}
	return 0;
}
