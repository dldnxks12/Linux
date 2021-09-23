// 클라이언트는 FIFO 파일을 열고 키보드로 부터 데이터를 입력받아 서버로 해당 데이터를 출력한다.

// 서버 코드는 bg로 실행한 다음 클라이언트 코드를 실행한다. 


#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFOFILE "fifo"

int main(int argc, char* argv[])
{

	int n, fd;
	char buf[BUFSIZ];

	if( (fd = open(FIFOFILE, O_WRONLY)) < 0)
	{
		perror("open()");
		return -1;
	}

	while( (n = read(0, buf, sizeof(buf))) > 0 ) // stdin에서 입력 (fd = 0)
	{
		write(fd, buf, n); // fd buffer에 n을 쓴다.
	}

	close(fd);
	return 0;

}
