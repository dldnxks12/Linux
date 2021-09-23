
// cat command 만들어보기
// cat = concatenate == 연결하다라는 의미로, cat과 redirect를 사용하면 file과 file을 연결할 수 있다.
// cat a b c > out  --- file a , b, c 를 연결해서 out에 쓴다.

// 원래 cat 명령어는 여러 인자들을 써서 다양한 기능을 사용할 수 있지만, 이번 예제에서는 가장 간단하게만 구현한다.

// cat.c : 인자로 file 1개 이상을 받아 해당 파일의 내용을 전부 표준 출력에 쓰는 프로그램 !

#include <stdio.h>  // header for std io
#include <stdlib.h>
#include <unistd.h> // header for UNIX system call
#include <sys/types.h> // ssize_t size_t 등의 데이터 type을 정의해둔 header file
#include <sys/stat.h> // header for file Info
#include <fcntl.h>    // header for file attribute setting

static void do_cat(const char *path); // cat function
static void die(const char* s); // close() error시 stderr 출력 후 exit(0)으로 프로세스 강제 종료
#define BUFFER_SIZE 2048

int main(int argc, char* argv[]) // ./cat filename
{

	int i;

	if(argc < 2)
	{
		fprintf(stderr, "%s file name is not given enough\n", argv[0]); // fprintf -> stream 출력 fd 설정 가능
		exit(1);
	}

	for (i = 0; i < argc; i++)
	{
		do_cat(argv[i]); // all file path에 대해서 do_cat 수행!
	}

	exit(0); // process 종료 -- return을 사용하지 않는 이유는 우리가 !직접! stream을 close()로 닫을 것 이기 때문
}

static void do_cat(const char* path) // file을 열고 읽는 함수
{
	int fd; // file descriptor
	unsigned char buf[BUFFER_SIZE];
	int n; // file 읽은 byte 수


	// path는 포인터 변수.. 인자로 넘겨줄 때? 그냥 포인터 변수 넘겨주면 된다. 
	fd = open(path, O_RDONLY);

	if(fd < 0)
		die(path); // fd가 -1이라면 ? 프로세스 종료
	for( ; ; )
	{
		n = read(fd, &buf, sizeof(buf));
		if(n < 0)
		{
			die(path);
		}
		if(n == 0)
		{
			break;
		}
		if(write(STDOUT_FILENO, buf, n) < 0 )
		{
			die(path);
		}
	}

	if(close(fd) < 0 )
	{
		die(path);
	}
}

static void die(const char* s)
{
	perror(s); // perror : 라이브러리 함수 , errno에 해당하는 값을 출력하고, s가 빈문자열이 아니면 같이 출력
	exit(1);
}
