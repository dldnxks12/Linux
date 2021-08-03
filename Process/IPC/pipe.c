// 파이프를 생성해서 부모 자식 간의 간단한 소통을 구현해보자
// 아래 코드는 자식 -> 부모로 현재 시간에 대한 메세지를 보내는 코드이다.

#include <stdio.h> // header for stdin stdout stderr
#include <unistd.h> // header for system call
#include <stdlib.h>
#include <sys/wait.h> // header for wait or waitpid

int main(int argc, char* argv[])
{

	pid_t pid;  // proces sid structure
	int pfd[2]; // file descriptor 배열 -> 파이프 인자로 넣어줄 것

	char line[BUFSIZ]; // 주고 받을 데이터 buffer
	int status;

	// pipe()를 통해 내부 file 생성
	if(pipe(pfd) < 0) // pipe error?
	{
		perror("pipe()"); // buffer를 거치지 않기 때문에 \n 불필요
		return -1;
	}

	if((pid = fork()) < 0) // fork() 함수로 process 생성
	{
		perror("fork()");
		return -1;
	}
	else if(pid == 0) // child process
	{
		close(pfd[0]); // 읽기를 위한 fd 닫기

		// dup, dup2 함수는 fd를 복제해서 return

		// dup2 : 두번째 인자가 첫 번째 인자로 가리키는 화살표 방향이 바뀐다.
		// 아래의 예는 pfd[1]이 가리키는 file로 stdout한다는 뜻
		// 즉, printf()를 하면 모니터가 아니라 pfd[1]의 file로 쓰여진다.

		dup2(pfd[1],1); // 쓰기를 위한 fd를 stdout (1) 로 변경
		execl("/bin/date","date",NULL); // date command 수행 -> 출력 결과 pfd[1]에 출력
		close(pfd[1]); // 쓰기를 위한 fd 닫기
		_exit(127); // exec 함수가 실패한 경우에 status가 127의 값. 만약 127이라면 이라면 종료
	}
	else  // parent process
	{
		close(pfd[1]); // 읽기할 거니까 쓰기 fd 닫기
		if(read(pfd[0], line, BUFSIZ) < 0 )
		{
			perror("read()");
			return -1;
		}
		printf("%s", line); // fd로 부터 읽은 내용을 화면에 출력?
				// 왜 화면이지? 아까 fd를 stdout으로 돌려놓지 않았나?
				// 아마 pfd[1]을 닫으면서 원래대로 돌아가지 않았나 싶다
		close(pfd[0]); // 읽기 fd 닫기
		waitpid(pid, &status, 0); // 자식 프로세서 종료되는 것 기다리기
	}

	return 0;

}
