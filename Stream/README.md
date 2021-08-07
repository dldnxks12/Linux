### 스트림

	Linux에서 Stream은 바이트의 흐름, 즉 byte stream을 의미한다.

	Linux(UNIX)의 입출력은 대부분 다음 4개의 시스템 콜로 모두 처리한다.

		1. read()  : Stream에서 바이트 열 읽기, 가져오기 

		2. write() : Stream에 바이트 열 흘려보내기

		3. open()  : Stream 열기

		4. close() : 다 쓴 Stream 닫기


#### File descriptor 

	프로세스에서 파일을 읽거나 쓸 때, 또는 다른 프로세스와 통신할 때, stream을 사용한다. 

	커널이 stream을 열 때, 이 stream에 대해 특수한 번호를 제공하는데 이것이 fd이다.

	fd를 이용해서 특정 stream에 접근, 사용 사용할 수 있다.


#### FILE type - p 93 모두를 위한 ~

	시스템 콜 레벨에서는 stream을 지정하기 위해 fd를 사용했다.

	한편, stdio (표준 입출력)에서는 비슷한 역할을 위해 'FILE 형에 대한 포인터를 사용한다.'

	FILE 구조체 안에는 fd와 stdio 버퍼의 내부 정보를 포함한 멤버 field들이 들어있다.

		즉, FILE type은 파일 디스크립터를 감싸고, 버퍼링 기능을 추가한 구조체이다 !!

		이처럼 기존의 기능을 감싸고, 추가 기능을 씌운 것을 wrapper (래퍼)라 한다. 

	ex) fopen(3) -- 3은 라이브러리 함수임을 의미 (section 3)

		표준 입출력 외에 stream에 대한 FILE을 여는 것도 가능! (FILE은 fd와 비슷한 stdio 레벨의 stream)

			(내부적으로 당연히 open() 시스템 콜을 사용한다.)

		#inlcude <stdio.h> 

		FILE* fopen(const char* path, const char* mode);

#### 바이트 단위 입출력

	+ fgetc(), fputc() / getc(), putc() / getchar(), putchar() / ungetc() --- p 95 참고 

#### 줄 단위 입출력

	+ fgets(), fputs() / printf() , fprintf() / scanf() / fread(), fwrite()

		! fgets와 비슷한 gets가 있는데, 이 놈은 절대 절대 사용하면 안된다.

		버퍼 오버플로우를 발생시키는데, 조용히 다른 프로그램이나 데이터를 파괴시킬 수 있다

		! scanf도 gets()와 비슷한 이유로 잠재적으로 버퍼 오버플로우를 발생시킬 위험이 있다.

#### 파일에 연결된 스트림

	stream에서 바이트 열을 꺼내는 것을 read(), 읽는다고 한다.
	
	stream에 바이트 열을 흘려 보내는 것을 write(), 쓴닫고 한다. 


		Process <-> Stream <-> File

#### 디바이스에 연결된 스트림

	바이트 열이 흘러갈 수 있는 곳이면 stream이 연결될 수 있다.

	SSD, HDD, 키보드, 모니터도 device file로 취급되므로, 당연히 스트림이 연결될 수 있다.

	
		Process <-> Stream <-> HW 

 #### PIPE

	스트림의 양 끝에 프로세스가 있는 구조이다.

	이 때의 Stream을 pipe라고 한다.

		Process <-> Stream <-> Process

#### 네트워크 통신

	Stream이란 바이트 열의 통로이다. 이게 잘 송신 된다면 다른 PC 까지 연결될수 있다.

	이것이 네트워크 통신!

		Process (내 PC) <-> Stream <-> Process (다른 PC)

#### IPC

	파이프나 네트워크 통신과 같이 프로세스 간의 Stream을 통한 데이터 송수신을 일반적으로 IPC라 한다.

	하지만 Stream만이 유일한 통신 방법은 아니다!

		POSIX IPC는 스트림을 사용하지 않는다.

			1. named semaphore
	
			2. message queue 

	
