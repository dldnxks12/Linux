#### UDP Network Programming

---

- UDP 

	UDP 프로토콜은 데이터의 전송 시 신뢰성은 없지만 일단 속도가 빠르다.

	따라서 데이터의 유실이 적은 LAN 환경에서 자주 사용한다. 

	UNIX에서 UDP 프로토콜을 이용한 통신을 하려면 socket() 함수의 인자로 SOCK_DGRAM을 설정하면 된다.


<div align=center>

![image](https://user-images.githubusercontent.com/59076451/130133942-46643306-760c-4164-b482-a474f5ffd7c5.png)

</div>

	일반적으로 UDP 서버와 클라이언트의 구현 방법은 비슷하다.

	하지만 서버의 경우 bind()함수를 사용해서 운영체제의 해당 포트로 들어오는 서비스를 UDP 서버에서 사용할 수 있게

	연결(등록)해주어야 한다. 

	UDP 서버와 클라이언트 모두 recvfrom() , sendto() 함수를 통해 데이터그램을 주고 받는다. 

	소켓 사용이 모두 끝나면 close() 함수를 써서 닫아주자!

---

- Socket

	UNIX에서 인터넷 통신을 하기 위해서는 먼저 소켓을 생성해야한다. - socket() 

	socket() 함수 호출에 성공하면 소켓에 대한 file descriptor를 반환하고, 실패하면 -1을 반환한다.

		socket(int domain, int type, int protocol)	

			1. domain : 소켓의 통신 방식 - 인터넷으로 통신할 건지 내부적인 파일 시스템을 이용할 건지!

			2. type   : 소켓의 전송 방식 - TCP or UDP

				
				SOCK_STREAM : stream socket은 TCP 기반의 신뢰성이 필요한 통신에 사용

				SOCK_DGRAM  : datagram socket은 UDP 기반의 빠른 속도가 필요한 통신에 사용

			3. protocol : 네트워크 프로토콜을 의미하는데 지금은 걍 0으로 쓰면 된다. 


	**소켓이 열린 후에 반환된 소켓의 file descriptor를 이용해서 통신을 진행할 수 있다!**

---

- 서버를 위한 bind()함수 


	UDP 서버를 생성하기 위해서는 bind() 함수를 사용해서 클라이언트로부터 들어오는 서비스를 

	현재의 Application이 사용할 수 있도록 해당 포트를 OS에 등록하는 작업을 수행해야 한다.

			bind()함수는 TCP 서버에도 사용한다!

	
	bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)

		1. sockfd  : socket의 file descriptor
		2. *addr   : UDP 서버의 주소 정보
		3. addrlen : 주소의 크기 

---

- UDP data 송/수신 - read(), write(), recvfrom(), sendto(), connect() ... 

	TCP의 경우 서버가 연결되어있기 때문에 read(), write() 같은 fd를 조작하는 함수를 이용해서 데이터를 송수신할 수 있다.

	하지만 UDP의 경우 서버와 연결되어 있지 않으므로 다른 함수를 사용해야한다 - recvfrom(), sendto()

		UDP는 sendto() 함수에 데이터를 받을 상대방의 정보(주소와 포트 번호)를 입력한다.

		UDP는 recvfrom() 함수로 데이터를 보낸 상대방의 정보를 받아올 수 있다.


	하나의 서버랑만 통신하는 경우라면 UDP도 connect() 함수를 이용해서 서버에 접속하고 read(), write() 함수를 통해서 통신을 수행할 수 있다.

		일반적으로 recvfrom(), sendto()함수는 데이터를 주고 받을 때 네트워크를 연결하고, 용무가 끝나면 연결된 네트워크를 끊는다. 

		하지만 connect() 를 이용하면 네트워크 연결을 지속할 수 있기 때문에 빠른 속도로 데이터를 주고 받을 수 있다.

---

- 주소 체계 

	주소 체계는 사용하는 도메인에 따라 다르다.

	Unix 내부에서 통신을 하는 경우

		sockaddr_un 구조체를 사용하고, 주소로 파일의 위치를 사용한다.

	Network 통신을 사용하는 경우

		sockaddr_in 구조체를 사용하고, 서버의 IP 주소와 포트 번호를 사용한다. 


	위 두 개의 구조체를 하나로 통합하는 구조체는 sockaddr이다. 


	인터넷을 사용하는 경우에는 sockaddr_in을 사용하면 되고, 서버의 주소와 포트 번호를 등록해야한다.

	서버의 주소는 서버의 IP주소를 사용하면 되는데, IP주소가 자주 변경되는 환경에서는 INADDR_ANY를 사용하면 자동으로 

	서버의 주소를 채워준다. 

	포트번호의 경우에는 앵간하면 5000번 이후의 포트 번호를 사용한다. 

---


- Byte 순서 변환 (Big Endian & Little Endian)

			Intel 계열 CPU : Little Endian

			SUN 계열 CPU   : Big Endian 

	네트워크 상에서는 데이터를 보내는 순서에 따라 Endian이 달라질 수 있다. 

	데이터는 순차적으로 보내지는데, 이런 이유로 Big Endian이 더 적합하다 - 앞 대가리 먼저 보내기

	이를 **네트워크 바이트 순서** 라고 하는데, 송/수신 데이터 모두 Big Endian으로 생각하고 처리해야한다.

			일반적으로 PC에서 사용하고 있는 CPU는 Intel 계열 .. (little endian)

			따라서 Endian 변환이 필요할 수 있는데, UNIX에서 이를 위한 다양한 함수를 제공한다.


	hton : host to network의 endian 변환
	
	ntoh : network to host의 endian 변환 
	
	
			IP주소는 32bit 이므로, Long형인 htonl()을 사용하면 되고, Port 번호는 16bit 이므로, short형인 htons()를 사용하면 된다.
			
---

- 네트워크 주소 변환 - p351


	IP 주소의 경우 '127.0.0.1'과 같은 문자열을 사용하는데, sockaddr_in의 sin_addr에 사용하는 값은 16진수의 정수값이다.

	따라서 이 문자열을 16진수로 변환해야한다. 

		문자열 '127.0.0.1'을 16진수 또는 2진수의 숫자로 된 IP 주소로 바꾸고 싶다면 POSIX 버전의 inet_pton()함수를 사용할 수 있다. 



	
			


	
