### Process & Thread 

- Process

     프로세스는 실행 중인 프로그램을 말한다.

    → 생성, 준비, 대기, 실행완료 등의 다양한 상태를 가지고 있다. 
	- CPU는 한 순간에 하나의 프로세스만 처리할 수 있기 때문에 다른 프로세스들은 대기해야 한다.
		- CPU를 사용하기 위해 CPU 시간을 분할해서 프로세스에 할당한다.
		- 시분할 시스템에서는 CPU에서 프로세스들이 돌아가면서 실행 
			- CPU의 Core는 매순간 하나의 프로세스만 실행 -> 주기를 아주 짧게 나누면 여러 프로그램이 동시에 수행되는 것 처럼 보인다.
			- 이렇게 나누어진 짧은 시간을 Quantum time 이라 한다.
			- Quantum time 단위로 나누어진 여러 프로세스들이 돌아가면서 실행되는데, 이 프로세스들은 프로세스 Queue에 의해 관리된다.
	- 프로세스들은 각각의 상태를 가지는데, 이 상태를 관리하는 PCB(Process Contro Block)에 이 상태를 저장한다.

    → Linux에서는 시분할 알고리즘을 통해 프로세스를 제어하는데, 이를 통해 여러 개의 일을 동시에 할 수 있다. ⇒ Thread 

![2222](https://user-images.githubusercontent.com/59076451/127248997-42663385-cd00-40f1-8095-92d9e4ad7acc.jpg)

- Process Data Structure

	사용자 구조 -> 프로세스 테이블 -> 프로세스 영역 테이블(가상 메모리) -> 메모리(실제 메모리)

	사용자 구조는 프로세스 수행 중에 필요한 정보를 저장한다. user structure는 <user.h> header에 정의 되어 있다.
	프로세스 테이블은 프로세스 관리에 필요한 정보들을 저장한다.

	- 리눅스에서 프로세스에 대한 정보는 task_struct 구조체를 통해 관리된다.
		- 위 구조체는 프로세스에 관한 모든 정보를 보관한다.
		- 아주 많은 구조체 멤버로 이루어져 있다.
			- task_struct 구조체에 대한 정보는 ps 명령어를 통해 불러올 수 있다.
			- 현재 실행되는 프로세스들의 정보는 /proc 디렉터리를 통해 확인할 수 있다.
				- ls /proc/

- Process command in CLI

	ps : process check

		pid : process id
		ppid : parent process id
		STAT : state of process 
			- P : 실행 가능 or 실행 중
			- D : 인터럽트 할 수 없는 대기 상태 
			- S : 20초 미만의 Sleep 상태
			- I : 20초 이상 길게 잠든 상태
			- R : CPU를 점유하기 위해 대기하고 있는 상태
			- Z : Zombie 상태 (프로세서가 종료될 때, 다른 문제로 인해 완전히 완료되지 못한 상태를 의미)
			- T : 일시정지 상태

	kill : process kill

	top : 현재 시스템의 프로세스 우선순위, CPU 등의 시스템 사용량 정보
		***특히 아래와 같은 정보를 알 수 있다.***
		- 프로세스의 우선 순위 (PR)
		- 프로세스의 경쟁 상대 (Race Condition)
		- Zombie Process
		- 메모리 누수 (Memory Leak)

		- 프로세스 우선 순위
			UNIX 스케쥴러는 모든 프로세서에게 우선순위를 부여한다.
			우선 순위가 높은 프로세서일수록 높은 프로세스 시간을 할당받고 자주 수행된다..
			Linux의 nice command를 통해 프로그램이 시작될 때 우선순위 값을 부여할 수 있다.
			"sudo nice -n-10 ls "

				PR : 프로세스의 우선순위
				NI : NICE(nice value)의 값으로 마이너스 값을 가지는 값이 우선순위 높다.
				- -20~+19 까지의 범위를 가지며, 값이 작을 수록 우선 순위가 높다.

![111](https://user-images.githubusercontent.com/59076451/127248996-5c2800a9-5306-4e94-99dd-22d3b2a1f5aa.PNG)


- Process background or foreground

	Linux에서 여러가지의 App을 동시에 실행할 수 있다.
	일반적으로 App을 실행하면 foreground 모드로 실행되고, 사용자의 Keyboard 입력이나 terminal로 출력할 수도 있다.
	하나의 terminal에서 foreground 모드로는 하나의 App만 실행할 수 있다.
		여러개의 App을 동시에 실행하려면 다른 App들은 backgorund mode로 실행한다.

	현재 foreground로 실행중인 process -> background로 실행하려면 Ctrl+Z를 입력 

	background로 App을 실행하고 싶다면 실행을 위한 명령어 뒤에 &를 붙인다 ex) ./loop &
	다시 foreground 모드로 바꾸려면 fg %[작업번호] 를 입력한다.

	
- Signal

    시그널은 프로세스들 사이에서 비동기적인 사건의 발생을 전달하는 방법 - Softward 적인 Interrupt로 생각할 수 있다.
	- 프로세스는 다른 프로세스에 시그널을 전달/설정할 수 있고, 해당 프로세스는 비동기적으로 시그널을 받아서 처리할 수 있다.
	- 예를 들어 SIGCONT 시그널은 같은 세션에 있는 임의의 프로세스에 전달할 수 있다.

    → C프로세스를 실행하는 도중 Ctrl+C 를 누르면 OS에서 Interrupt를 의미하는 Signal을 발생시키고 이를 해당 process에 전달하여 중단시킬 수 있다. 

    → 숫자를 0으로 나누는 등의 error를 알리기 위한 signal

    → Linux에서 이러한 signal을 처리하는 방법도 지원한다.
	- 실행 중인 프로세스는 사용자가 terminal에서 ctrl+c or ctrl+z를 눌러 발생하는 interrupt에 의해 멈추거나 중지된다.
	- 이 때 OS에서 Signal이 발생해 해당 process에 전달된다.


	signal()함수 -> 시그널이 발생하면 보통 기본 설정값으로 처리된다. 하지만 프로세스 내에서 해당 시그널에 대해서 처리를 지정할 수도 있다!
	시그널을 처리하기 위해서는 시그널 핸들러를 생성한 후 signal() 함수를 통해 시그널을 등록하면 된다.

	#### 아래 signal() 함수는 c언어 문법을 이해하기 위함 
	
	signal() 함수의 첫 번째 인자 signum으로는 처리하고 싶은 Signal 명을 사용하면 된다.
	두 번째 인자로는 시그널을 처리하기 위한 시그널 핸들러를 등록하는데, 핸들러는 시그널이 발생하면 호출될 함수의 주소를 준다. 

	#include <signal.h> // header for signal , more -> kldp.org/node/158641
	
	typedef void (*sighandler_t)(int); // function alias + function pointer 

	sighandler_t signal(int signum, sighandler_t handler) // function pointer return 
	
	// typedef 를 걷어내면 더 자명하게 보인다.
	// sighandler_t signal( int signum, void(*sighandler_t)(int) )


	-> 시그널이 발생하면 이를 받아서 미리 등록된 시그널 핸들러가 실행되는데, SIGKILL, SIGSTOP 시그널에는 시그널 핸들러를 등록할 수 없다!	
	

- fork() , exec()

    멀티 프로세스 환경에서 (동시에 여러 개의 프로그램을 돌리는 것) 새 프로세스를 생성

    → fork() 함수 사용

    → 일반적으로 client의 요청에 따라 동일한 서비스를 제공하는 네트워크 서비스(naver)의 경우, 하나의 프로세스를 복제해서 부모와 자식이 동시에 각각 관련된 기능을 실행할 수 있다.

    → fork() 함수로 자식 프로세스를 생성한 다음 exec() 함수로 새로운 프로그램을 실행

    → POSIX에서는 fork와 exec을 함께 실행하는 posix_spawn() 함수를 제공

- IPC (Inter Process Protocol) - Pipe, FIFO, 공유 메모리

    프로세스들 간에 공유하는 공간이 없기 때문에 이들 끼리 소통하는 방법이 필요하다.

    이를 위한 IPC로 파이프, FIFO, 공유 메모리 등의 방법이 사용된다.

    → Pipe : 부모 자식 프로세스 간에만 서로 소통이 가능

    → FIFO : 모든 프로세스들 간에 소통이 가능

- Thread

    스레드는 일의 처리 단위로 프로세스에 비해 빠르게 생성할 수 있다.

    또한 서로 공유되는 메모리를 이용해서 서로 간의 데이터를 전달할 수 있다.

    → 즉, 프로세스에 비해 빠르게 생성되고, 메모리를 공유한다.

    → 하지만 모든 스레드가 같은 메모리를 공유하기 때문에 동기화 문제가 발생할 수 있다.

    → 세마포어 or 뮤텍스를 이용해서 해결
