#include <stdio.h>  // header for standard IO
#include <stdlib.h> // header for exit

// File pointer, nlines : 읽을 줄 수
static void do_head(FILE* f, long nlines);

#define _GNU_SOURCE
#define DEFAULT_N_LINES 10
#include <getopt.h> // header for option parsing

// option 이라는 구조체 배열을 전역 변수로 생성
/*
다음과 같은 방법으로 구조체 배열을 선언하면서 초기화 가능

struct 구조체 p[3] = {
	{값1, 값2},
	{값3, 값4},
	{값5, 값6}
}

*/


static struct option longopts[] = {

	//{char* name, int has_arg, int* flags, int val}

	// name    : 옵션 이름 help 등등
	// has_arg : 인자
	// flags   :  NULL ? getopt_long이 val 값을 반환, !NULL ? getopt_long이 0을 반환하고, *flag에 val 값을 대입
	// val     :  flag의 값에 따라 지정한 곳에 반환할 값
	{"lines", required_argument, NULL, 'n'},
	{"help", no_argument, NULL, 'h'},
	{0,0,0,0} // 맨 마지막에는 모든 멤버를 0으로 만든 struct option을 추가해주어야 한다.

};

int main(int argc, char* argv[])
{

	int opt;
	long nlines = DEFAULT_N_LINES; // 10

	// getopt_long(argc, argv, 해당 옵션 문자들, optin의 정의,  )
	// longopts 라는 구조체를 통해 해당 option을 지정한다.
	while( (opt = getopt_long(argc, argv, "n", longopts, NULL)) != -1 )
	{
		switch(opt){

		case 'n':
			nlines = atol(optarg); // optarg : 현재 처리 중인 옵션의 파라미터
			break;
		case 'h':
			fprintf(stdout, "Usage: %s [-n LINES] [FILE ... ]\n", argv[0]);
			exit(0); // 정상 종료
		case '?':
			fprintf(stderr, "Usage: %s [-n LINES] [FILE ...]\n", argv[0]);
			exit(1); // 에러 메세지 종료
		}
	}

	if(optind == argc) //getopt_long에 의한 parsing이 끝난 시점에서 optind == argc? 즉, 옵션 외에 추가 인자 x!
	{
		do_head(stdin, nlines);
	}
	else
	{
		int i;

		for(i = optind; i<argc; i++)
		{

			FILE* f;

			f = fopen(argv[i], "r");

			if(!f)
			{   //(f == NULL)
				perror(argv[i]);
				exit(1);
			}

			do_head(f, nlines);
			fclose(f);
		}

	}
	exit(0); // 정상 종료
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
			return;
		}
	}
}
