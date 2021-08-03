// 커맨드 라인 인자에 대한 이해
// int main(int argc, char* argv[])에 대해 -> argv는 문자열을 담은 배열
// char *str = "hello"
// char **str = ["hello", "buddy", "double"]

#include <stdio.h>
#include <stdlib.h> // header for exit() function

int main(int argc, char* argv[]) // or char** argv
{
	int i;

	printf("argc = %d\n", argc);

	for(i = 0; i < argc; i++)
	{
		printf("argv[%d] = %s\n", i , argv[i]); // 문자열 하나씩 출력
	}

	exit(0);
}
