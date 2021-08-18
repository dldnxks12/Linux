// 특정 값을 넣을 버퍼 확보하는 방법 - path를 써넣을 버퍼 확보하는 법

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define INIT_BUFSIZE 1024 // 1024로 일단 setting

char* my_getcwd(void)
{
	char* buf, *tmp;
	size_t size = INIT_BUFSIZE;

	buf = malloc(size); // 동적 메모리 할당
	if(!buf)
	{
		return NULL;
	}

	for(;;)
	{
		errno = 0;
		if(getcwd(buf, size))
		{
			return buf;
		}

		if(errno != ERANGE) // 만일 if getcwd() 문을 건더 띄었는데 ERANGE가 아니라면 정지 -- buffer 딱 맞게 읽음
		{
			break;
		}

		size = size*2; // 크기 2배로
		tmp = realloc(buf, size); // 동적 메모리 키우기
		if(!tmp)
		{
			break;
		}

		buf = tmp;
	}

	free(buf);

	return NULL;
}

int main(int argc, char* argv[])
{

	char* path;


	path = my_getcwd();


	printf("%s\n", path);

	return 0;
}


