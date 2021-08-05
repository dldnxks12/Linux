// 2 개의 프로세스를 만들어서 부모 프로세스와 자식 프로세스가 같은 메모리 공간을 함께 이용하는 예제이다.

// 먼저 2개의 프로세스를 생성한다.
// 이후 shmget() 함수를 사용해서 공유 메모리에 대한 채널을 가져온다.
// 이후 shmat() 함수를 이용하여 공유 메모리를 현재 프로세스의 공간에 연결시킨다.
// 채널에 대한 제어는 shmctl()로, 공유 메모리와 프로세스와의 연결 해제는 shmdt()로 수행한다.

#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>

#define SHM_KEY 0x12345 // ipcs -m 명령어 수행 시 key 값 확인 가능

int main(int argc, char* argv[]){

	int i, pid, shmid;
	int *cVal;
	void *shmmem = (void *) 0; //  == NULL - pointer 변수 초기화

	if( (pid = fork()) == 0) // creat process
	{
		shmid = shmget((key_t)SHM_KEY, sizeof(int), 0);
		if(shmid == -1){
			perror("shmget()");
			return -1;
		}


		// 공유 메모리 사용을 위해 공유 메모리와 프로세스 묶기
		shmmem = shmat( shmid, (void*)0, 0666 | IPC_CREAT); // 2번째 인자 (void*)0  or NULL 으로 할 경우 적절히 주소 배정
		if(shmmem == (void*)-1) // 성공하면 적절한 포인터 넘겨주고, 실패하면 void* 0 return
		{
			perror("shmat()");
			return -1;
		}

		cVal = (int*)shmmem; // void 형 포인터니까 형 변환해서 사용
		*cVal = 1; // cVal 의 역참조해서 1 값 넣어주기 (공유 메모리에 이렇게 접근)

		for(i = 0; i<3; i++)
		{
			*cVal += 1;
			printf("Child (%d) : %d\n", i , *cVal); // child process id , cVal value return
			sleep(1);
		}

	}

	else if(pid > 0)
	{
		shmid = shmget((key_t)SHM_KEY, sizeof(int), 0666 | IPC_CREAT);
		if(shmid == -1)
		{
			perror("shmget()");
			return -1;
		}

		shmmem = shmat(shmid, (void*)0 , 0);
		if(shmmem == (void*)-1)
		{
			perror("shmat()");
			return -1;
		}

		cVal = (int *)shmmem; // cVal은 주소 공유 메모리 주소 why? shmmem이 주소를 가지고 잇으니까!
		for(i = 0 ; i<3; i++)
		{
			sleep(1);
			printf("Parent(%d): %d\n", i , *cVal); // 1초마다 해당 주소에 대한 값 출력
			// child process가 1초에 한 번씩 증가시키고 있으니까 1초에 한 번씩 값 증가할 것 
		}
	}

	shmctl(shmid, IPC_RMID, 0);

	return 0;

}
