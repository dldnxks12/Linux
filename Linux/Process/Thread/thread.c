/*

gcc 컴파일 시 pthread 라이브러리 링크 필요

 	gcc -o thread thread.c -pthread

Thread 사용법

	- 자세한 설명은 reakwon.tistory.com/56

스레드 생성 : pthread_create()

스레드 대기 : pthread_join()

	프로세스를 생성한 후 자식 프로세스를 대기하는 것 처럼 thread도 종료할 때 까지 기다려야한다.
	서브 스레드가 실행 중일 때는 메인 스레드가 종료되면 안된다.

	이 함수는 생성했던 thread가 끝날 때까지 기다려준다.

	만약 이미 thread가 종료되었다면 즉시 return한다. 성공시 0 return 실패 시 error return

	실패 시에는 좀비 스레드가 되고, 이 좀비 스레드가 자원을 소모하게 되서 더이상 스레드를 생성할 수 없게 된다.


		메인 스레드 : main() 함수

		일반적으로 메인 스레드가 종료되면 서브 스레드 들도 함께 종료된다.

스레드 분리 : pthread_detach()

	메인 스레드에서 pthread_create()로 만든 스레드를 분리하고 싶은 경우 사용한다.

	분리된 스레드가 종료될 경우 pthread_join() 함수를 호출 안해도 알아서 모든 자원을 해제한다.


		즉, 메인 스레드가 나는 기다려주지 않을거고, 끝나면 알아서 끝내라 ~ 하는 것 


+++ pthread_self() : 현재 Thread 식별자 확인

	pthread_t pthread_self(void);

*/


#include <pthread.h> //  header for thread !!
#include <stdio.h>   // header for std io
#include <unistd.h>  // header for System Call
#include <stdlib.h>


void* thread_routine(void* arg){ // sub thread

	pthread_t tid; // thread id

	tid = pthread_self(); // thread id 식별자 return

	int i = 0;

	printf("\t tid : %lx\n", tid);
	while(i<10)
	{
		printf("\t New Thread : %d\n", i);
		i++;
		sleep(1);
	}
}


int main() // main thread
{

	pthread_t thread;  // thread 구조체 선언 --- 스레드를 구분하기 위한 ID


	// 아래 함수 호출에 성공하면 thread에 ID를 설정하고 0을 return
	// (thread 구조체, thread attribute, 실행할 함수 포인터, 해당 함수에 넘겨줄 인자)
	pthread_create(&thread, NULL, thread_routine, NULL);

	int i = 0;
	printf("tid : %lx\n", pthread_self());
	while(i<5)
	{
		printf("main: %d\n", i);
		i++;
		sleep(1);
	}

	pthread_join(thread, NULL); // thread_routine의 return 값이 없으므로 NULL 로 설정 

}




















