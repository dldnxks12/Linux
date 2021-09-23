// system() 함수는 fork(), exec(), wait() 함수를 한 번에 실행할 수 있는 함수이다.
// 이 함수를 위 세 개 함수를 이용해서 구현해본다.

// system() 함수는 stdlib.h header file에 구현되있으므로, 이 header file을 import 하지 않도록 주의한다.

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> // header for function wait()
#include <errno.h>

int system(const char *cmd) // fork, exec, waitpid 함수 사용
{

	pid_t pid; // process id
	int status;

	if( (pid = fork() ) < 0 ) // fork() 수행 시, child process id return
	{
		status = -1; // fork() error시
	}
	else if( pid == 0 ) // 자식 프로세스 처리
	{
		execl("/bin/sh", "sh", "-c", cmd, (char *)0);
		_exit(127); // exec 함수가 실패하면 생성한 프로세스의 종료 값으로 status에 127 을 리턴
		// _exit(int status) ->
	}
	else
	{	// waitpid -> 자식 프로세스 없다면 -1 return
		while(waitpid(pid , &status, 0) < 0 ) // 자식 프로세스 종료 대기
		{
			if(errno != EINTR)
			{
				status = -1;
				break;
			}
		}

	}

	return status;
}

int main(int argc, char* argv[], char* envp[]) // envp : 환경 변수
{

	// 그냥 char envp[] 를 받아왔다면 envp는 배열의 주소를 가리킴
	// 즉, *envp는 이중 포인터니까, *envp는 envp[]의 처음 주소를 가키리는 것

	while(*envp)
	{
		printf("%s\n", *envp++); // ["path1", "path2", "path3" , ... ] -> *envp는 path1 을 가리키고 하나씩 증가
	}

	system("who"); // who 유틸리티 수행
	system("nocommand"); // 오류 사항의 수행
	system("cal"); // cal 유틸리티 수행 


	return 0;
}
