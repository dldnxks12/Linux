## POSIX IPC 

#### POSIX Message Queue 

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

	
	해당 directory의 message queue source code를 build 할 때 rt(realtime) 라이브러리를 함께 링크해야 한다.

		gcc -o posix_msg_server posix_msg_server.c -lrt

![55](https://user-images.githubusercontent.com/59076451/128531377-7d732cb5-178c-4bd7-ac3c-499e411f05a4.PNG)
	
#### POSIX Semaphore

	Linux에서는 XSI에서의 세마포어를 더 쉽게 사용할 수 있는 라이브러리 형태의 함수를 제공한다.

	이를 네임트 세마포어라고 한다.


		- 초기화 -- sem_open()
	
			세마포어를 사용하기 전에 반드시 sem_t 형을 초기화 해야한다.
	
			초기화는 sem_open() 함수를 사용한다.

			sem_open()의 첫 번째 인자로 다른 세마포어와 구분할 수 있는 이름이 들어가는데, 

			이 때문에 네임드 세마포어라고 부른다. 

		
		- P, V -- sem_post(), sem_wait()

			초기화를 진행한 후 P연산과 V 연산을 수행할 수 있다.

			이는 sem_post(), sem_wait() 함수로 수행한다.

		- 세마포어 사용 종료, 제거 -- sem_close(), sem_destroy()

			사용이 다 끝난 세마포어는 sem_close()로, 제거는 sem_destroy()로 수행한다.

		- 세마포어 삭제 -- sem_unlink()


			sem_open()으로 세마포어를 생성하여 사용이 끝난 후 더 이상 필요가 없어졌을 때, 

			sem_unlink()로 세마포어를 삭제할 수 있다.

	해당 directory의 네임드 세마포어 source code를 빌드할 때 pthread 라이브러리를 링크해주어야 한다.

		gcc -o posix_sem posix_sem.c -pthread


		
