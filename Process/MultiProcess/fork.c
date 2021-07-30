// fork 함수를 사용하면 새 프로세스를 생성하는데, 부모 프로세스와 자식 프로세스가 생성된다.
// pid_t fork() 함수에서 반환값이 pid_t 구조체를 통해 자식과 부모를 구분한다.
// 반환된 PID가 0 자식 프로세스고, 0 또는 -1이 아니면 무조 프로세스이다.

// fork() 함수를 이용해서 프로세스를 생성하는 코드
// 전역 변수와 지역 변수 1개씩 생성해서 프로세를 생성하고 바꿔보자.
// 전역 변수와 지역 변수 중 어떤 것이 변하고 어떤 것이 안변하나? 그 이유는?

#include <stdio.h>
#include <unistd.h> // Header for Unix System Call

static int g_var = 1; // data 영역의 초기화된 전역 변수 -> process 복제 시 data 영역은 복제할 뿐 메모리를 공유하지 않는다.
char str[] = "PID";

int main(int argc, char* argv[])
{

	int var; // stack 영역의 지역 변수 -> process 복제 시 stack, heap 영역은 복제할 뿐 메모리 공유 x
	pid_t pid; // pid_t 구조체 -> process id를 담고 있는 type
	var = 92;

	if((pid = fork()) < 0 ) // fork() 수행 오류
	{
		perror("[ERROR] : fork()");
	}else if(pid == 0)
	{
		g_var++; // 전역 변수값 변화
		var++;   // 지역 변수값 변화

		printf("Parent %s from Child Process %d : %d\n", str, getpid(), getppid());
	}else
	{
		printf("Child %s from Parent Process %d : %d\n", str, getpid(), getppid());
		sleep(1);
	}

	printf("pid = %d, Global var = %d, var = %d\n", getpid(), g_var, var);

	return 0;  // exit() 함수 호출
}

