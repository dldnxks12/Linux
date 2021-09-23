#include <sys/types.h> // header for various data type
#include <sys/ipc.h>   // header for ipc key, channel
#include <sys/msg.h>   // header for message queue

#include <stdio.h>
#include "msg_data.h"
#include <string.h> // strcpy를 위한 header
#include <stdlib.h> // header for exit()

int main(int argc, char* argv[]){

	key_t key = 12345; // 메세지 큐 채널 생성을 위한 key 생성. type은 key_t로 항상 동일
	int msqid;

	struct message msg; // msg_data header에 정의해놓은 구조체 변수 선언


	// 메세지 큐 ID 받아오기 (채널 생성 or 확인)

	// flag IPC_CREATE -> 없으면 생성, 있으면 해당 channel id return
	if( (msqid = msgget(key, IPC_CREAT | 0666)) == -1){
		printf("msgget()");
		exit(0); // 프로세스 종료
	}

	// 메세지 받기

	printf("Message Queue Receiver Start");

	if( msgrcv(msqid, &msg, sizeof(struct real_data), 0, 0) == -1){
		printf("msgrcv()");
		exit(0);
	}

	printf("name : %s , age : %d\n", msg.data.name, msg.data.age);

	// 이후 메세지 큐 채널 제거 - 자원 반납

	if( msgctl(msqid, IPC_RMID, NULL) == -1 ){
		printf("msgctl()");
		exit(0);
	}

	printf("Message Queue Receiver End\n");
}











