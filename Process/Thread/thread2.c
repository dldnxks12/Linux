// POSIX 세마포어 함수를 Thread를 이용해서 구현해본다.
// POSIX 세마포어는 동기화 관리에 사용되는 기법으로써 P연산, V연산을 통해 메모리를 관리하에 둘 수 있다.

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>   // header for thread
#include <semaphore.h> // header for POSIX semaphore

sem_t* sem; // POSIX Semaphore를 사용하기 위해 반드시 semaphore 구조체를 초기화시켜야한다.
static int cnt = 0; // Semaphore에서 사용할 임계 변수

void p()
{
	sem_post(sem);
}

void v()
{
	sem_wait(sem);
}

void* pthreadV(void* arg) // V 연산을 수행하기 위한 함수 - pthreadP 함수와 동시에 수행될 것
{
	int i;
	for(i = 0; i < 10; i++)
	{
		if(cnt >= 7)
			usleep(100); // cnt 7이상 -> 100 ms 대기

		cnt++;
		printf("Increase : %d\n", cnt);
		fflush(NULL); // buffer에 있는 값 강제로 모두 출력
		v();
	}

	return NULL;
}

void* pthreadP(void* arg)
{

	int i;
	for(i =0; i < 10; i++)
	{
		// p() 연산을 수행한다는 것은 메모리 임계 영역에 들여보내겠다는 뜻
		// 여기선 간단하게 걍 p 함수에서 세마포어 변수를 줄이거나 늘리기만 한다.
		p(); // Semaphore( value in main thread )가 0이 되면 block된다.
		cnt--;
		printf("Decrease : %d\n", cnt);
		fflush(NULL);
		usleep(100); // 100ms wait
	}
	return NULL;
}

int main(int argc, char* argv[])
{

	pthread_t ptV, ptP; // thread 구조체 변수 선언

	const char* name = "posix_sem"; // semaphore 이름
	unsigned int value = 7; // semaphore 변수. 이거 0 되면 임계 영역 출입 제한

	sem = sem_open(name, O_CREAT, S_IRUSR | S_IWUSR, value ); // 세마포어 생성

	// 함수는 이름 그 자체로 포인터다 아래와 같이 걍 주면됨 (& 이딴거 생각도 하지마라)
	pthread_create(&ptV, NULL, pthreadV, NULL);
	pthread_create(&ptP, NULL, pthreadP, NULL);

	// 이제 위 thread들이 종료하기 전에 main thread가 종료하지 않도록 안전장치를 달자

	pthread_join(ptV, NULL);
	pthread_join(ptP, NULL);

	sem_close(sem); // 다 쓴 세마포어 닫기
	printf("sem_destroy() : %d\n", sem_destroy(sem)); // 세마포어 정리하기

	sem_unlink(name); // 세마포어 삭제

	return 0;
}
