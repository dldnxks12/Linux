
// 메세지 큐 예제 --- reakwon.tistory.com/97
// 메세지 큐를 사용하기 위해 다음 3개의 header file이 필요


// msgget : 메세지 큐 채널 생성해서 ID 또는 번호 return -> key값과 flag를 인자로 넣어주면 된다. \
//	 - (key ? 서버와 클라이언트가 같은 key 값을 가져야한다. 이를 이용해서 메시지 큐 채널 (or ID) 얻을 수 있다.)

// msgctl : 메세지 큐 제어
// msgsnd : 메세지 보내기
//	msgsnd가 성공적으로 수행되면 msqid_ds 구조체의 field가 변경된다.
// 	msg_lspid는 호출된 프로세스 id로 변경 , msg_qnum 1증가, msg_stime을 현재 시간으로 설정

// msgrcv : 메세지 받기

// msgbuf 구조체를 이용해서 데이터를 주고 받는다 -> sys/msg.h header에 정의되어있다.

#include <sys/types.h> // header for various data type
#include <sys/ipc.h>   // header for ipc key, channel
#include <sys/msg.h>   // header for message queue

#include <stdio.h>
#include "msg_data.h"
#include <string.h> // strcpy를 위한 header
#include <stdlib.h> // header for exit()


// Message Information View
void printMsgInfo(int msqid){

	struct msqid_ds m_stat;

	printf("========== Message Queue Info ==========\n");

	if(msgctl(msqid, IPC_STAT, &m_stat) == -1){
		printf("msgctl()");
		exit(0);
	}

	printf(" Message Queue Info \n");
	printf(" msg_lspid : %d\n", m_stat.msg_lspid);
	printf(" msg_qnum  : %ld\n", m_stat.msg_qnum);
	printf(" msg_stime : %ld\n", m_stat.msg_stime);


	printf("========== Message Queue Info End ==========\n");
}

int main(int argc, char* argv[]){

	key_t key = 12345; // 메세지 큐 채널 생성을 위한 key 생성. type은 key_t로 항상 동일
	int msqid;

	struct message msg; // msg_data header에 정의해놓은 구조체 변수 선언
	msg.msg_type = 1;
	msg.data.age = 80;
	strcpy(msg.data.name, "JongSoo");

	// 메세지 큐 ID 받아오기 (채널 생성)

	if( (msqid = msgget(key, IPC_CREAT | 0666)) == -1){
		printf("msgget()");
		exit(0); // 프로세스 종료
	}

	// 메세지를 보내기 전 msqid_ds 구조체 field 값들을 보자 !
	printMsgInfo(msqid);

	// 메세지 보내기

	if( msgsnd(msqid, &msg, sizeof(struct real_data), 0) == -1){
		printf("msgsnd()");
		exit(0);
	}

	printf("Message Sent!!\n");

	printMsgInfo(msqid);
}











