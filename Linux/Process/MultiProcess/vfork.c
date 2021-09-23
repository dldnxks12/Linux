#include <stdio.h>
#include <unistd.h> // Header for Unix System Call

static int g_var = 1; 
char str[] = "PID";

int main(int argc, char* argv[])
{

	int var; 
	pid_t pid; // pid_t 구조체 -> process id를 담고 있는 type
	var = 88;

	// *** vfork() 함수 호출 후 프로세스가 나뉘고, 바로 아랫 줄 부터 실행 ***
	// vfork()는 exec() 또는 exit() 함수 호출전까지 메모리를 공유하므로, child process가 먼저 실행되는 것을 보장
	if((pid = vfork()) < 0 ) // fork() 수행 오류
	{
		perror("[ERROR] : fork()");
	}else if(pid == 0) // child process에 대해서 먼저 수행 !
	{
		g_var++; // 전역 변수값 변화
		var++;   // 지역 변수값 변화
		printf("Parent %s from Child Process %d : %d\n", str, getpid(), getppid());
		printf("pid = %d, Global var = %d, var = %d\n", getpid(), g_var, var);
		_exit(0); //*** 자식 프로세스는 _exit() 함수를 통해 종료해주어야함. ***
			  // return문으로 종료를 해버리면 프로세스들 사이에 공유된 함수의 stack도 삭제되므로
			  // 부모 프로세스를 종료할 시 error가 발생 !

	}else 		  // parent process에 대해서 수행
	{
		printf("Child %s from Parent Process %d : %d\n", str, getpid(), getppid());

	}

	printf("pid = %d, Global var = %d, var = %d\n", getpid(), g_var, var);

	return 0;  // exit() 함수 호출
}

