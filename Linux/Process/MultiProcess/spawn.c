// posix_spawn() 함수 인자
// 1. pid 인자 2. 두번 째 인자로 exec() 함수와 같이 실행할 프로그램의 경로
// 3. 4. posix_spawn() 함수의 속성 -> 기본 속성은 NULL 값
// 5. 마지막으로 두 번째 인자로 넣어서 실행할 프로그램에서 사용할 인자를 넣어준다.
// 6. 환경 변수

#include <stdio.h> // header for standard Input Output (stdin, stdout, stderr)
#include <sys/wait.h> // header for wait() or waitpid()
#include <spawn.h> // header for poxis_spanw() -> for fork() + exec()

extern char ** environ; // posix function or exec 의 환경 변수 인자를 담아서 넘겨줄 전역 변수

// char cmd[] 이렇게 받아와도 상관 x -> 배열 매개변수
int system(char *cmd) // system() 함수가 stdlib.h header에 정의되어있기 때문에 import 하면 안된다.
{

	pid_t pid;
	int status;
	char *argv[] = {"sh", "-c", cmd, NULL}; // 실행할 프로그램에 넘겨줄 인자

	// pid 구조체 , 실행할 프로그램 경로 / 속성 / 속성/ 프로그램에 넘겨줄 인자/ 환경 변수
	posix_spawn(&pid, "/bin/sh", NULL, NULL, argv, environ);

	waitpid(pid, &status, 0); // 자식 프로세스가 정상 종료하면 pid 값 return, 비정상 종료 -> status에 상태 저장

	return status;
}


int main(int argc, char* argv[], char*envp[])
{

	while( *envp)
	{
		printf("%s\n", *envp++); // 또는 for 문으로 envp[i] 이렇게 해도 됨 -> envp 배열의 문자열 하나씩 출력
	}

	system("who");
	system("nocommand");
	system("cal");

	return 0;

}
