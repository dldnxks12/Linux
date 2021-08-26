// 프로세스 간 통신인 IPC에도 Socket을 사용할 수 있다.
// socketpair() 함수는 주소를 갖지 않는 한 쌍의 소켓을 생성하고, 이를 통해 부모, 자식 프로세스간 통신을 할 수 있다.

// socket 함수는 PIPE나 FIFO와 다르게 양방향 통신이 가능하다 하지만, 다른 UNIX 도메인에 있는 프로세스와는 통신 불가!

// 기본적인 코드는 PIPE를 이용하는 것과 비슷하다.

#include <stdio.h>  // header for standard io
#include <unistd.h> // header for UNIX system call
#include <string.h> // header for string function
#include <wait.h>   // header for process wait
#include <sys/socket.h> // header for socket

int main(int argc, char* argv[]){

	int ret, sock_fd[2];  // socket에도 file descriptor를 사용해서 stream을 표현한다.
			      // socketpair() 함수로 2개의 socket fd를 받아서 배열로 저장할 것

	int status;
	char buf[] = "Hello World";
	char line[BUFSIZ];
	pid_t pid; // Process type

	// AF_LOCAL or AF_UNIX : socketpair는 로컬에서만 통신이 가능하기에 이렇게 flag를 준다.
	// SOCK_STREAM : stream 통신을 위한 flag
	ret = socketpair(AF_LOCAL, SOCK_STREAM, 0, sock_fd); // 한 쌍의 Socket을 생성해서 sock_fd에 담아 return
	if(ret == -1)
	{
		perror("socketpair()");
		return -1; // return 은 내부적으로 exit()를 call해서 buffer를 모두 비우고 종료시킨다.
	}

	// socket descriptor 번호 출력
	printf("Socket 1: %d\n", sock_fd[0]);
	printf("Socket 2: %d\n", sock_fd[1]);

	if((pid = fork()) < 0) // Process 생성
	{
		perror("fork()");
	}else if(pid == 0) // Child Process
	{
		write(sock_fd[0], buf, strlen(buf) + 1); // Parent Process로 데이터 보내기

		close(sock_fd[0]);
	}else
	{
		read(sock_fd[1], line, BUFSIZ);
		printf("Received Data : %s\n", line);

		close(sock_fd[1]);
	}

	return 0;
}

