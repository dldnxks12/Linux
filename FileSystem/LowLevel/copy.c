/*

하나의 파일의 내용을 다음 파일로 복사하는 코드 작성
Application을 실행하면 명령행 인수로 2개의 filename을 입력받고,
2개의 file을 열거나 생성한 후 첫 번째 file에서 데이터를 읽어서 두 번째 file로 쓰자.

출력 시 표준 입출력 라이브러리 이용할 때 printf를 사용 
but when use only low level IO -> use write()
Also use error 출력 to stderr (모니터에 연결) with perror  (prror : 표준 에러 출력을 위한 표준 입출력 함수)
  -> stderr 은 2번 fd
  -> stdin  -> 0번 
  -> stdout -> 1번 

  -> 즉, perror를 사용해서 error 출력 하거나, write의 fd 를 2로 설정하여 error 출력 가능 

*/

#include <unistd.h> // for Unix System Call
#include <fcntl.h>  // for file setting or modifying
#include <stdio.h> // standard in out - perror()
#include <sys/types.h>
#include <sys/stat.h>

// file call -> with 2 argv 1. filename 2. copied filename

int main(int argc, char** argv)
{

	int n , in , out; // for file descriptor
	char buf[1024]; // for buffer

	if (argc < 3)
	{
		write(2, "Usage : copy file1 file2",25);  // 2 : stderr fd
		return -1;
	}

	// read file
	if ( (in = open(argv[1], O_RDONLY)) < 0 )
	{
		perror(argv[1]);
		return -1;
	}

	// open write file with create new file | erase existed file mode 
	// privailage : read and write to file owner 
	if ( (out = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR)) < 0 )
	{
		perror(argv[2]);
		return -1;
	}

	// read file and write file
	while ( (n = read(in, buf, sizeof(buf))) > 0 )
		write(out, buf, n);

	close(in);
	close(out);

	return 0;
}

