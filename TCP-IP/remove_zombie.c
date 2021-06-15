//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <signal.h>
//#include <sys/wait.h>
//
//void read_childproc(int sig)
//{
//	int status;
//	pid_t id = waitpid(-1, &status, WNOHANG);
//	if (WIFEXITED(status))
//	{
//		printf("Removed proc id : %d \n", id);
//		printf("Child send: %d \n", WEXITSTATUS(status);
//	}
//}