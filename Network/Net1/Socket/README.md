#### 네트워크 통신을 위한 API

	가장 신경써야할 부분은 Stream을 여는 open()에 해당하는 부분이다.


	Socket 

		Linux에서는 네트워크 통신을 위해 Socket을 사용한다.

		이 Socket은 스트림을 연결하기 위해 사용한다. 

		
	Client Socket API

		Client 쪽에서 서버에 스트림을 연결하기 위해서는 다음의 두 가지 API를 사용한다. 

		1. socket(2)  - 소켓을 만드는 System Call
		2. connect(2) - 연결한 대상에 대한 정보를 Connect()에서 지정해서 스트림을 연결한다. 

	Server Socket API

		Server 쪽에서는 스트림의 연결을 기다리고 있다. 다음의 네 가지 API를 사용한다.

		1. socket(2)
		2. bind(2)   
		3. listen(2)  
		4. accept(2)


	IP Arre <-> Host name 

		1. getaddrinfo()  - host name으로부터 IP주소, Port 번호를 얻는데 사용 
		2. getnameinfo()  - IP주소, Port 번호로부터 host name을 얻는데 사용
		3. freeaddrinfo() - 보조용 API
		4.gai_strerror()  - 보조용 API



		

		

		
