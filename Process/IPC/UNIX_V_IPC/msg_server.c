// p295 message Queue 

#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h> // ipc 통신을 위한 system call 이 정의된 header file
#include <sys/msg.h> // header for message queue

#define MSQKEY  12345

struct msgbuf{

	long mtype;
	char mtext[BUFSIZ]; // 여기에 메세지 담아서 나를 것

};

int main(int argc, char* argv[])
{
	key_t key; // channel 생성을 위해 필요한 key
	int n;
	int msqid; // Server와 Client 사이의 소통을 위한 channel id 생성


	struct msgbuf mb;

	key = MSQKEY;

	// 메세지 큐 채널 생성

	if( (msqid = msgget(key, IPC_CREAT | IPC_EXCL | 0666 )) < 0)
	{
		perror("msgget()");
		return -1;
	}

	// 메세지 큐에서 데이터 가져오기 - msgrcv
	while( (n = msgrcv(msqid, &mb, sizeof(mb),0 ,0)) > 0 )
	{
		switch(mb.mtype){

			case 1:	// 메세지 출력
				write(1, mb.mtext, n); // write to where?  stdout으로 fd = 1 : stdout
				break;
			case 2: // msq 삭제
				if(msgctl(msqid, IPC_RMID, (struct msqid_ds *)0) < 0)
				{
					perror("msgctl");
					return -1;
				}
				break;
		}


	}

	return 0;
}
