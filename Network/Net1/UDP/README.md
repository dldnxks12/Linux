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


			


	
