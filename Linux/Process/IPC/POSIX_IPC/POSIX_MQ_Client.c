#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <mqueue.h>

int main(int argc, char* argv[])
{

	mqd_t mq; // message queue 객체 생성 mqd_t 는 tag로써 struct 구조체의 alias
	const char* name = "/posix_msq"; // 메세지 큐 끼리 공유할 이름

	char buf[BUFSIZ];

	mq = mq_open(name, O_WRONLY); // 새로 메시지 큐를 만들지 않고, 있는 것을 열기

	// hello world 라는 문자열 보낸 후 , 다시 'q'를 보내서 서버를 종료시킨다.

	// 메세지 큐의 사용이 끝나면 mq_close()로 메세지 큐를 닫지만, 큐를 삭제시키지는 않는다.

	strcpy(buf, "hello world!\n");
	mq_send(mq, buf, strlen(buf), 0);

	strcpy(buf, "q");
	mq_send(mq, buf, strlen(buf), 0);

	mq_close(mq);

	return 0;

}
