// stdio의 바이트 단위 입출력 함수를 사용해서 cat 함수를 구현

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{

	int i;

	for(i = 0; i< argc; i++)
	{
		FILE* f; // FILE 구조체 포인터 fd의 wrapper
		int c;

		f = fopen(argv[i], "r");
		if(!f)
		{
			perror("argv[i]");
			exit(1);
		}

		while((c = fgetc(f)) != EOF)
		{
			if(putchar(c) < 0)
			{
				exit(1);
			}
		}

		fclose(f);

	}

	exit(0);

}
