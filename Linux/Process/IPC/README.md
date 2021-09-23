### 프로세스 사이의 통신 IPC (Inter Process Communication)

일반적으로 프로세스 간에는 공유되는 부분이 없기 때문에 서로 통신을 하기 위해 방법이 필요!


1. Simple IPC 

		- 버퍼로 사용할 file을 하나 만들어 놓고 이 file을 경유해서 데이터를 쓰고 읽는 방법

		- file 입출력(fread, fwrite)을 통해 통신 가능 

			1. 파이프 (단뱡향)

			2. FIFO (단뱡향)

			3. Socket (양방향) 

	** 문제 

		- OS에 따라 다르지만 일반적으로 하나의 프로세스가 하나의 file을 열 수 있기 때문에 여러 프로세스가 접근할 때 충돌이 발생할 수 있다. 

		- 즉, 입출력 다중화 시 문제 해결이 어렵다. 또한 시스템 콜이 빈번해서 OS kernal에 부하가 심하다.

	- 따라서 위와 같은 문제를 보완한 통신 방법으로 Posix IPC가 개발되었다.

2. UNIX V / XSI IPC (X System Interface)

		- UNIX V / XSI IPC 통신 방법은 기존 PIPE, FIFO, Socket과 달리 file을 경유하지 않는다.
			
			1. 메세지 큐
		
			2. 세마포어

			3. 공유 메모리 

		위 3가지 방법은 UNIX 시스템 V에서 처음 제안된 IPC로 각 IPC 기법은 독특한 특징이 있다.

		각 방법마다 고유의 시스템 Call을 사용하기 때문에 기존 파일 시스템에서 제공하는 System Call을 사용할 수 없다. 

		- UNIX SYSTEM V에서 설정된 IPC 채널 정보를 확인하고 싶을 떄는 다음 명령어를 사용하자

			$ ipcs [-q | -m | -s] 

				또한 채널 생성과 삭제는 다음 명령어를 사용한다.

				& ipcmk , & ipcrm
		

- Header File 

	메세지 큐 : <sys/msg.h>

	세마포어  : <sys/sem.h>

	공유 메모리 : <sys/shm.h>


- IPC 채널 생성/열기

	메세지 큐 : msgget()

	세마포어 : semget()

	공유 메모리 : shmget()


- IPC 채널 제어/삭제 

	메세지 큐 : msgctl()

	세마포어 : semctl()

	공유 메모리 : shmctl()


- IPC 동작

	메세지 큐 : msgsnd(), msgrcv()

	세마포어 : semop()

	공유 메모리 : shmat(), shmdt()


- 네임스페이스 : 생성 가능한 채널 이름의 집합  (채널 : 우리 통신할 건데 채널을 열어야 통신을 하지 !)

- UNIX System V의 IPC에서는 모든 키에 동일한 key_t 타입을 사용한다. (key? 통신하려면 누가 누군지 서로 알아봐야지!)

- 키는 ftok() 함수로 생성 가능하며, 프로세스가 채널 이름 할당을 요청할 때, 커널은 동일한 채널 이름을 중복 할당하면 안된다. 

	키를 생성한 후 msgget(), semget(), shmget() 함수와 같이 Unix 시스템 V의 IPC 채널을 가져올 수 있다.

		key와 여기에 해당하는 채널 할당 (이 Key와 채널로 통신할 것 !)

	세 함수 모두 첫 인자로 키 값을 사용하고 마지막 인자로 flag 값을 사용한다. (p291 참고)

	
	IPC 채널을 가져오면 msgctl(), semctl(), shmctl() 함수를 통해 IPC 동작을 수행할 수 있다. 



3. POSIX IPC 
		
		UNIX V/XSI IPC 통신의 취약점을 보완하기 위해 발전된 통신 방법 

		- UNIX V IPC 보다 더 직관적인 API로 사용하기 쉽다!
	
		- POSIX IPC 통신 방법은 file을 경유하지 않는다.

			1. 메세지 큐

			2. 네임드 세마포어

			3. 공유 메모리 (mmap)


		
#### IPC 간단 특징

파이프 : 부모 프로세스와 자식 프로세스 사이에서만 Only 통신 가능 

FIFO, 소켓, 메세지 큐, 공유 메모리 : 서로 관계없는 프로세스 사이에서도 통신 가능		                                                                                                                                                                                                                                                                                                                                       

#### IPC (Inter Process Communication)

![111](https://user-images.githubusercontent.com/59076451/127955308-db00bcdb-1a70-40e8-a2a8-e48c7473e5fc.jpg) 




