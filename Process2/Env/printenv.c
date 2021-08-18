// 현재 프로세스의 환경 변수를 모두 표시하는 코드

#include <stdio.h>
#include <stdlib.h>

extern char **environ; // 해당 변수는 외부 file에 정의되어있다.

int main(int argc, char*argv[])
{

	char **p;

	for(p = environ; *p; p++)
	{
		printf("%s\n", *p);
	}

	exit(0);
}


