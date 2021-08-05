// p295 message Queue 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> // strcpy 를 위해 include
#include <string.h> // 문자열 다루기 위해 include
#include <sys/msg.h> // header for message queue

#define MSQKEY  12345

struct msgbuf{

	long mtype;
	char mtext[BUFSIZ]; // 여기에 메세지 담아서 나를 것

};

int main(int argc, char* argv[])
{
	key_t key; // channel 생성을 위해 필요한 key
	int rc;
	int msqid; // Server와 Client 사이의 소통을 위한 channel id 생성

	char* msg_text = "hello jongsoo\n";

	struct msgbuf *mb;

		// 자료형 변환 + msgbuf 구조체 포인터 + msg 크기만큼 메모리 할당
	mb = (struct msgbuf*)malloc(sizeof(struct msgbuf*) + strlen(msg_text)); // 동적 메모리 할당

	key = MSQKEY;

	// 메세지 큐 채널

	if( (msqid = msgget(key, 0666 )) < 0)
	{
		perror("msgget()");
		return -1;
	}

	mb->mtype = 1;

	strcpy(mb->mtext, msg_text);

	rc = msgsnd(msqid, mb, strlen(msg_text)+1, 0);

	if(rc == 1)
	{
		perror("msgsnd()");
		return -1;
	}

	mb->mtype = 2;

	memset(mb->mtext, 0, sizeof(mb->mtext)); // mb.mtext memory 0으로 초기화
	if( msgsnd(msqid, mb, sizeof(mb->mtext),0) < 0 )
	{
		perror("msgsnd()");
		return -1;
	}
	return 0;
}
