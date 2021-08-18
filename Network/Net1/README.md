#### Linux Network Programming 


	IP Addr

		인터넷에 연결된 호스트는 반드시 IP 주소와 Port 번호를 가지고 있다. 이를 통해 특정 호스트를 알 수 있다.

		해당 호스트에서는 특정 Port에서 어떤 신호가 오기를 기다리는 프로세스가 돌아가고 있다. 

			이렇게 접속을 기다리면서 어떤 작업을 해주는 프로세스를 "서버 프로세스" 라고 한다.

			반대로 서버에 접속해서 어떤 작업을 수행하는 프로세스를 "클라이언트 프로세스"라고 한다. 

		

		그럼 어떤 서버 프로세스가 어떤 Port로 대기 중인지 알 수 있는 방법은 뭘까?

		이것은 사전에 공유되지 않는 한 알기 어렵지만, 유명한 서비스들은 정해진 Port를 사용한다. 

			ex) 메일 서버 (SMTP) : 25 port , 웹 서버 (HTTP) : 80 port, ... 

				/etc/services 에 나열되어있다. 

		
	TCP/UDP 


		IP 보다 상위 layer인 TCP/UDP Level에서는 btye 열인 stream을 전송한다.

		이를 잘라 패킷으로 만들어 IP layer에 내려보내 전송한다. 

		받는 쪽에서는 잘려긴 패킷을 보고 잘 맞춘 후 byte 열을 만들어 스트림으로 받아들인다.
	
		


	Host name 

		네트워크 상의 호스트(PC)는 IP 주소로 식별된다. 하지만 IP주소는 숫자이므로 사람이 다루기 어렵다.

		따라서 이 IP주소 대신에 Host name을 이용한다. 

			ex) www.google.com 

		Host name과 IP 주소를 매칭시켜놓으면 사람은 외우기 쉽고 쓰기 쉬운 host name을 사용하고,

		PC는 이를 IP 주소에 해당하는 숫자로써 다루면 된다.

		
	DNS (Domain Name System)

		호스트에 대해서 IP 주소와 host name을 모두 매칭시켜 놓은 저장소라고 보면 된다. 

		DNS는 host name을 domain 이라고 하는 영역에 나눠서 관리하고, 이를 전 세계에 알린다.

		domain이라 함은 , com, org, kr 등의 이름을 가진 name을 관리하는 이름 영역이다.

		만일 com 이라는 이름을 가진 host name을 찾는다면, com domain을 관리하는 DNS 서버에 물어봐야하는 것이다. 
			
