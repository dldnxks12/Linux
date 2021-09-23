#include <stdio.h>  // standard IO
#include <fcntl.h>  // file setting
#include <unistd.h> // Unix System Call header
#include <termios.h> // terminal : device like moniter and keyboard



// keyboard event 

int keyboardhit(void)
{

	struct termios oldt, newt; // terminal 구조체
	int ch, oldf;

	tcgetattr(0, &oldt); // fd : 0 -> stdin 즉, keyboard fd에 대한 terminal 속성을 oldt에 복사
	newt = oldt; // oldt -> newt로 복사
	newt.c_lflag &= ~(ICANON | ECHO); // 정규모드 입력과 Echo를 해제 -> 모니터로의 출력을 해제

	tcsetattr(0, TCSANOW, &newt); // 새로운 값으로 terminal 설정
	oldf = fcntl(0 , F_GETFL, 0); // 기존 flag 저장
	fcntl(0 , F_SETFL, oldf | O_NONBLOCK); //기존 flag + Non blocking mode로 설정

	ch = getchar(); // 문자를 buffer에 받고 화면에 출력 -> but 화면 출력하지 않도록 설정함

	// getchar() -> stdin(입력 stream) -> 입력 버퍼 -> 프로그램 -> 출력 버퍼 -> stdout(출력 stream) -> 데이터 버퍼에서 사라진다.
	// but 출력 과정 제거  ( 입력 버퍼에 있는 값을 ch로 받아두기만 함)
	tcsetattr(0, TCSANOW, &oldt); // 기존 값으로 다시 terminal 0 (stdin) setting
	fcntl(0, F_SETFL, oldf); // file setting도 기존 값으로

	if(ch != EOF)
	{
		ungetc(ch, stdin); // 앞에서 꺼낸 문자를 stream에 다시 넣기 (stream에 다시 입력으로)
		// -> 문자 ch를 stdin stream에 입력으로 넣어주기 
			// stdin stream -> input buffer 
		return 1;
	}
	return 0;
}

int main(int argc, char** argv)
{
	int i =0;

	for(i; ; i++)
	{
		if(keyboardhit())
		{
			// stream에 이미 값을 넣어주었기 때문에 추가적으로 keyboard로 입력 안해도 될 듯 
			switch(getchar()) // stream에 있는 문자 읽기 -> input buffer로 받기 -> 화면 출력 
			{
				case 'q':
					goto END;
					break;
			};
		}
		printf("%20d\t\t\r",i);
		usleep(100);
	}

END:
	printf("Good bye\n");
	return 0;

}



