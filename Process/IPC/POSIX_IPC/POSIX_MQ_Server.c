// 서버에서 통신을 위한 메세지 큐를 mq_open() 함수로 생성한다.
// mq_receive() 함수를 통해 클라이언트에서 데이터를 받아온다.
// 가져온 데이터를 화면에 출력하고, 만일 'q'가 들어왔다면 메세지 큐를 닫고 프로그램을 종료한다.

#include <stdio.h>
#include <unistd.h> // header for System Call

#include <mqueue.h> // header for POSIX Message Queue

int main(int argc, char*argv[])
{

	mqd_t mq; // 메세지 큐 형 == mqd_t type
	struct mq_attr attr; // message queue attribute 를 가져오고 설정하기 위한 구조체 변수 선언

	const char *name = "/posix_msq"; // message queue 끼리 공유할 이름
	char buf[BUFSIZ];
	int n; // receive 된 data 확인할 변수

	// 메세지 큐 attribute 초기화
	attr.mq_flags   = 0;
	attr.mq_maxmsg  = 10;
	attr.mq_msgsize = BUFSIZ;
	attr.mq_curmsgs = 0;

	// 메세지 큐 생성 and 획득 --- mqd_t type 반환받고, 이를 이용할 수 있다.
	mq = mq_open(name, O_CREAT | O_RDONLY , 0644, &attr);

	// 메시지 큐에서 데이터 가져오기 --- client에서 data 보내주면 queue에서 꺼내올 것
	while(1)
	{
		n = mq_receive(mq, buf, sizeof(buf), NULL);
		switch(buf[0])
		{
			case 'q':
				goto END;
				break;
			default :
				write(1, buf, n); // stdout에 buf 내의 n개 데이터 write
				break;
		}
	}

END :
	mq_close(mq);  // 메세지 큐 닫기
	mq_unlink(name); // 큐 삭제

	return 0;

}
