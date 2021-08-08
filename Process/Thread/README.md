### POSIX Thread와 동기화

	UNIX에서 동시에 여러 가지 일을 처리하고 싶다면 멀티 프로세스를 이용할 수 있다.

		 가상 CPU와 가상 메모리를 이용한 여러 개의 프로세스 실행 방법 ..

	하지만 새로운 프로세스를 만들면 자신 만의 메모리 공간을 가져야하고, 동일한 작업을 수행하는 경우에 공유되는 부분 없이

	별도의 영역을 사용하기 때문에 메모리 공간의 낭비를 불러일으킨다.

	위 문제를 해결하기 위한 방안이 Thread이다. 

	Thread는 어떤 프로그램에서 프로세스가 실행되는 흐름의 단위를 말한다.
	
	즉, 프로세스는 적어도 1개의 thread를 가지고 있다. 

		우리가 흔히 알고 있는 main() 함수가 바로 해당 thread!

#### multi process VS multi thread

	멀티 프로세스와 멀티 스레드는 흐름이 동시에 진행된다는 점에서 동일하다.

	하지만 프로세스와는 다르게 멀티 스레드는 메모리를 공유한다.

		공유되는 영역은 text 영역 (기계어 코드), data 영역 (변수), file(heap) 영역이다.

![333](https://user-images.githubusercontent.com/59076451/128603079-54cf9b4c-f8e6-446e-9ce4-265cd7483476.PNG)

	위 그림과 같이 예를 들어 Thread가 3개 일 경우

	각각의 thread가 특정 시점에 프로그램의 특정 부분을 실행한다고 해보자.

	그렇게 하기 위해서는 CPU의 program counter(레지스터)와 stack을 독립적으로 가져야한다.

		각 thread가 서로 다른 부분을 수행하기 때문에 서로 다른 stack을 가진다.

		각 thread가 서로 다른 시각에 수행되기 때문에 서로 다른 PC를 가진다.


#### Thread

	Thread는 프로세스에서 나누어지는 일의 단위이다.

	1. Kernel Level Thread

	2. User Level Thread 

		일반적으로 Application에서는 이 유저 레벨 스레드를 사용한다.

		유저 레벨 스레드는 다른 스레드와 메모리를 공유할 수 있기 때문에 생성이 빠르고, 메모리 낭비를 막을 수 있다.
		
		! 하지만 한 스레드라도 메모리를 잘못 건드리면 다른 스레드에도 영향을 미치는 단점이 있다.

			이 문제를 해결하기 위해서 Thread 동기화 방법을 사용한다 - * Mutex 

	일반적으로 Thread 간에 전역 변수, Heap 메모리, 파일 디스크립터 등을 공유한다.

	프로세스와 마찬가지로 여러 가지일을 동시에 할 수 있지만, context switching이 프로세스보다 빠르다.

	또한 공유되는 메모리를 이용하므로 스레드 간의 통신이 IPC보다 간단하다.

		Context switching ? Kerner mode <-> User mode 의 mode Switching을 의미
		
![66](https://user-images.githubusercontent.com/59076451/128603441-a9140f91-1160-4fbe-8685-52bef6852327.jpg)

![444](https://user-images.githubusercontent.com/59076451/128603139-b3d26537-8dbf-4ca3-818b-b6e577a0a459.jpg)		


#### Thread 예제 1 실행결과

![thread1](https://user-images.githubusercontent.com/59076451/128605349-f77c1171-a917-4d95-b4b8-bd0a912ee00d.PNG)


#### Thread API

	1. thread 생성

		pthread_create()

	2. thread 대기

		pthread_join()

	3. thread 분리

		pthread_detach()

	4. thread id get

		pthread_self()

	5. thread 종료

		pthread_exit()

	6. thread 취소

		pthread_cancel()

	


	
