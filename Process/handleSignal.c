#include <stdio.h>
#include <signal.h> // signal() 함수
#include <stdlib.h> // exit() 함수
#include <string.h> // strsignal() 함수 : signal 번호에 대한 정보를 string으로
#include <unistd.h> // UNIX System Call


//sigset_t : 시그널 마스크를 다루기 위한 구조체
// 위 구조체의 signalSet은 정수형 변수로 표현하는데, 변수의 각 비트가 하나의 시그널을 지칭한다.
// 0 : clear , 1 : set
static void printSigset(sigset_t *set); // 현재 sigset_t에 설정된 signal 표시 , 구조체 포인터 사용 -> 구조체 주소 넘겨주기
static void sigHandler(int signo); // Signal 처리하기 위한 핸들러

int main(int argc, char*argv[])
{

	sigset_t pset; // sigset_t 구조체 사용 -> block 시킬 signal을 등록할 sigset_t 형 구조체
	sigemptyset(&pset); //signal bit 모두 0으로 초기화
	sigaddset(&pset, SIGQUIT); // 아래 2개의 Signal 설정
	sigaddset(&pset, SIGRTMIN) // SIGQUIT -> Terminal에서 Ctrl+\ 키, SIGRTMIN ->
	sigprocmask(SIG_BLOCK, &pset, NULL); // 현재의 시그널 마스크에 set 값 추가 (위 2개 signal에 mask 씌우기)

	printSigset(&pset); // 현재 설정된 sigset_t을 화면에 출력

	//SIGINT -> 인터럽트 , terminal에서 ctrl+c
	if(signal(SIGINT, sigHandler) == SIG_ERR) // SIGINT 처리를 위한 핸들러 등록
	{
		perror("signal() : SIGINT"); // perror 또는 stderr는 버퍼를 거치지 않고 바로 출력!
		return -1;
	}
	else if(signal(SIGUSR1, sigHandler) == SIG_ERR)
	{
		perror("signal() : SIGUSR1");
		return -1;
	}
	else if(signal(SIGUSR2, sigHandler) == SIG_ERR)
	{
		perror("signal() : SIGUSR2");
		return -1;
	}
	else if(signal(SIGPIPE, sigHandler) == SIG_ERR)
	{
		perror("signal() : SIGPIPE");
		return -1;
	}

	while(1)	// while은 왜 있을까?
	{pause();}     // pause() : signal 처리 될 때 까지 대기

	return 0;
}

static void sigHandler(int signo)
{

	if(signo == SIGINT)
	{
		printf("SIGINT is catched : %d\n", signo);
		exit(0); // program or process quit
	}
	else if(signo == SIGUSR1)
	{
		printf("SIGUSR1 is catched : %d\n", signo);
	}


}






