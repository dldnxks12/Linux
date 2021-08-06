## POSIX IPC 

#### POSIX 메세지 큐 

	XSI의 메세지 큐와 마찬가지로 프로세스 간에 데이터를 메세지의 형태로 전송할 수 있다. 

	XSI의 함수들이 시스템 콜인 것에 비해 POSIX 함수는 라이브러리 형태로 제공된다. -- mqueue.h

		--- System Call의 호출 빈도를 조절하여 Kernel에 부하를 줄인다.

	POSIX의 메세지 큐는 mqd_t type을 사용한다.


	XSI IPC  ---- POSIX IPC

	msgget() ---- mq_open()

	msgsnd() ---- mq_send()

	msgrcv() ---- mq_receive()


	mq_close()  함수로 프로세스의 큐 사용을 마친다.

	mq_unlink() 함수로 메세지 큐를 삭제할 수 있다. 
			
	mq_getattr() 함수로 메세지 큐의 속성을 얻을 수 있다.

	mq_setattr() 함수로 메세지 큐의 속성을 설정할 수 있다.

	추가적으로 mq_notify() 함수로 비동기적으로 오는 메세지에 대해 알람을 받을 수 있다. 



	
