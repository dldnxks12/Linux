// Semaphore의 P 연산, V 연산에 대한 함수를 만들고, 이를 이용해서 Semaphore를 동작시킨다.

#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h> // header file for semaphore

int cnt = 0;
static int semid;

void p() // P
{
	struct sembuf pbuf;

	pbuf.sem_num = 0;
	pbuf.sem_op  = -1; // sem_op 값 - 1
	pbuf.sem_flg = SEM_UNDO;
	if(semop(semid, &pbuf, 1) == -1) // 세마포어 감소연산 수행
		perror("p : semop()");
}

void v() // V
{

	struct sembuf vbuf;
	vbuf.sem_num = 0;
	vbuf.sem_op  = 1;
	vbuf.sem_flg = SEM_UNDO;
	if(semop(semid, &vbuf, 1) == -1) // 세마포어 증가연산 수행
		perror("v : semop()");

}


int main(int argc, char* argv[])
{

	// 공용체 선언
	// main 안에 선언 했기에 main 문 안에서만 사용 가능
	union semun{
		int val;
		struct semid_ds *buf;
		unsigned short int *array;
	}arg; // alias 설정

	// channel 생성

	if( semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666) == -1 )
	{
		perror("semget()");
		return -1;
	}

	arg.val = 1; // 세마포어 값을 1로 설정

	if( semctl(semid, 0, SETVAL, arg) == -1)
	{
		perror("semctl() : SETVAL");
		return -1;
	}


	while(1)
	{
		if(cnt >= 8)
		{
			cnt--;
			p();
			printf("decrease : %d\n", cnt);
			break;
		}
		else
		{
			cnt++;
			v();
			printf("increase : %d\n", cnt);
			usleep(100);
		}
	}

	// channel 삭제
	if( semctl(semid, 0, IPC_RMID, arg) == -1)
	{
		perror("semctl() : IPC_RMID");
		return -1;
	}

	return 0;
}
