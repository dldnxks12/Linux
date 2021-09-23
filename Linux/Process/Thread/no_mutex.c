// mutex 를 사용하지 않았을 경우 어떤 문제가 발생하는지 다음의 코드를 실행하여 확인해보자

#include <stdio.h>
#include <unistd.h> // header for UNIX system call
#include <pthread.h> // header for thread
#include <stdlib.h>

int cnt = 0; // 전역변수로 써 data 영역에서 메모리를 할당받는다. (초기값이 없다면 BSS Section에서 .. )

// 이 cnt 라는 변수에 두 개의 thread가 동시에 접근해서 값을 변화시키려고 할 것이다.

void* count(void* arg)
{


	int i;
	char* name = (char*)arg; // arg 변수의 type casting

	// --------- critical section --------- // -- cnt 값에 접근

	cnt = 0;
	for(i = 0; i < 10; i++)
	{
		printf("%s cnt : %d\n", name, cnt);
		cnt++;
		usleep(1);
	}
	// --------- critical section ---------- //
}


int main(int argc, char* argv[])
{

	pthread_t thread1, thread2;

	pthread_create(&thread1, NULL, count, "thread1");
	pthread_create(&thread2, NULL, count, "thread2");

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);


	return 0;
}
