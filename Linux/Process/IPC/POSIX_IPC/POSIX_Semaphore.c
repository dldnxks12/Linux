#include <stdio.h>
#include <unistd.h>
#include <fcntl.h> // header for O_CREATm O_EXEC 등의 매크로 (file attribute setting에 필요한 header file)
#include <semaphore.h>

sem_t *sem; // 세마포어를 위한 전역 변수
static int cnt = 0; // 세마포어에서 사용할 critical section 변수 --- S 라고도 표현한다.

void p()
{
	cnt--;
	sem_post(sem);
}

void v()
{
	cnt++;
	sem_wait(sem);
}

int main(int argc, char* argv[])
{

	const char* name = "posix_sem";
	unsigned int value = 8; // 세마포어 value

	sem = sem_open(name, O_CREAT , S_IRUSR | S_IWUSR, value);

	while(1)
	{
		if(cnt >= 8)
		{
			p();
			printf("decrease : %d\n", cnt);
			break;
		}
		else
		{
			v();
			printf("increase : %d\n", cnt);
			usleep(100);
		}
	}

	sem_close(sem); // 다 쓴 세마포어 닫기
	printf("sem_destroy return value : %d\n", sem_destroy(sem)); // 세마포어 제거하기

	// 세마포어 삭제
	sem_unlink(name); // 이 이름으로 된 세마포어는 이제 없다.

	return 0;

}








