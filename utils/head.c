#include <stdio.h>  // header for standard IO
#include <stdlib.h> // header for exit

// File pointer, nlines : 읽을 줄 수
static void do_head(FILE* f, long nlines);



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

		do_head(stdin, atol(argv[1])); // 표준 입력으로 넣어준 것을 바로 출력

	// file 인자가 있을 경우에는 해당 file의 내용을 출력
	else
	{
		int i; // file 인자 개수에 맞게

		for(i=0; i < argc; i++)
		{
			FILE* f; // FILE 구조체 포인터 생성
			f = fopen(argv[i], "r"); // 해당 file로 Stream 생성

			if(!f) // f == NULL 과 동일한 문장
			{
				perror(argv[i]);
				exit(1);
			}

			do_head(f, nlines);

			fclose(f); // FILE 구조체에 포함된 stream 닫기
		}
	}

	exit(0);

}


static void do_head(FILE* f, long nlines)
{
	int c;

	// fgetc(FILE* stream) -- stream에서 1 byte 씩 가져오기
	while( (c = fgetc(f)) != EOF )  // fgets를 사용하지 않는 이유? --- buffer를 만들어서 넘길 필요가 없다
	{
		// 읽은 1 byte를 stdout으로 보내기
		if(putchar(c) < 0) // putchar == fputc(int c, FILE* stream)   --- fputc(c, stdout)
		{
			exit(1);
		}
		if(c == '\n') // 개행 문자 만나면 줄 - 1
		{
			nlines--;
		}
		if(nlines == 0)
		{
			return 0;
		}
	}
}
