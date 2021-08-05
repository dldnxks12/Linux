
// 간단히 무한루프 process를 만든후 top 또는 kill command로 이 process를 제어해보자.

#include <unistd.h> // header for Unix System Call
#include <stdio.h> // header for stdin stdout stderr

int main(int argc, char* argv[])
{

	int i;

	// 1초마다 i를 증가시켜 출력
	for (i =0; ; i++)
	{
		printf("%10d\r",i); // i를 제자리에서 출력
 		fflush(NULL); // 열려있는 모든 출력 버퍼를 비운다. -> printf()에서 개행문자를 사용하지 않았으므로 우리가 직접 fflush 해주어야한다.
			      // fflush(stdout) : 표준 출력의 출력 버퍼를 강제로 비운다.
		sleep(1);
	}

	return 0;

}
