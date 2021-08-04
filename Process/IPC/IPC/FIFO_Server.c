// fifo server code

#include <stdio.h>
#include <unistd.h> // read(), write(), unlink() 등의 저수준 입출력을 위한 Unix System Call
#include <sys/stat.h> // file 상태정보 get
#include <fcntl.h> // header for file 정보 setting

#define FIFOFILE "fifo"

int main(int argc, char* argv[])
{

	int n , fd;
	char buf[BUFSIZ];

	unlink(FIFOFILE); // 기존의 FIFO file을 삭제 - 해당 파일과 연결된 file들 제거

	// int mkfifo(const char* path, mode_t mode)
	if( mkfifo(FIFOFILE, 0666) < 0 )
	{
		perror("mkfifo()");
		return -1;
	}

	// open(경로, 모드)
	if( (fd = open(FIFOFILE, O_RDONLY)) < 0 ) // fifo 열기
	{
		perror("open()");
		return -1;
	}

	while( (n = read(fd, buf, sizeof(buf))) > 0 )
	{
		printf("%s", buf); // 개행 문자는 필요없나?
	}

	close(fd);
	return 0;

}
