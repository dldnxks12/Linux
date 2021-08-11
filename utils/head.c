#include <stdio.h>
#include <stdlib.h>

static void do_head(FILE* f, long nlines);

// 첫 번째 인자는 받아들인 줄 수, 두 번째 인자는 파일 이름

int main(int argc, char* argv[])
{

	long nlines;

	if(argc < 2)
	{
		fprintf(stderr, " Argument Number Error \n");
		exit(1);
	}

	nlines = atol(argv[1]); // nlines 줄수 , atol --- 문자열 to long type 정수

	if (argc == 2) // file 인자가 없을 경우, stdin의 내용을 출력

		do_head(stdin, atol(argv[1]));

	// 해당 file의 내용
	else
	{
		int i;

		for(i=0; i<argc; i++)
		{
			FILE* f;
			f = fopen(argv[i], "r");

			if(!f) // f == NULL 과 동일한 문장
			{
				perror(argv[i]);
				exit(1);
			}

			do_head(f, nlines);
			fclose(f);
		}
	}

	exit(0);

}


static void do_head(FILE* f, long nlines)
{

	int c;

	while((c = fgetc(f)) != EOF)  // fgets를 사용하지 않는 이유? --- buffer를 만들어서 넘길 필요가 없다
	{
		if(putchar(c) < 0) // putchar == fputc(c, stdout)
		{
			exit(1);
		}
		if(c == '\n')
		{
			nlines--;
		}
		if(nlines == 0)
		{
			return 0;
		}

	}

}
