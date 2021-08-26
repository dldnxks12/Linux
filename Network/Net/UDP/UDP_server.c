// 소켓을 이용해서 UDP로 서로 통신하는 Code
// 클라이언트에게 받은 메세지를 그대로 돌려보내는 Echo 코드

#include <stdio.h>  // header for standard io
#include <string.h> // header for string function
#include <unistd.h> // header for UNIX system call
#include <sys/socket.h> // header for socket
#include <netinet/in.h> // header for network function

#define UDP_PORT 5100  // UDP port 번호 5100으로 설정

int main(int argc, char* argv[]){


	int sockfd; // socket file descriptor
	int n;

	struct sockaddr_in servaddr, cliaddr; // internet으로 통신할 거니까, sockaddr_in 구조체 사용
	socklen_t len; // socket addr length struct
	char msg[1000]; // Message

	// create socket for UDP
	sockfd = socket(AF_INET, SOCK_DGRAM, 0); //  AF_INET : IPv4 protocal , SOCK_DGRAM : UDP protocol

	// 이 프로그램을 서버로 쓰려면 OS에 서비스를 등록해야한다. - bind() 함수 이용

	// 접속되는 클라이언트를 위해 주소를 설정한 후 OS에 서비스 등록 할 것
	// bind() 함수로 servaddr 구조체에 IP, Port 설정하기 전 0으로 초기화 해주어야 함
	memset(&servaddr, 0, sizeof(servaddr));

	// hton 함수로 host->network의 endian으로 변환
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // IP주소가 동적으로 바뀌어도 되도록 INADDR_ANY flag 설정
	servaddr.sin_port = htons(UDP_PORT);

	// sockaddr_in type -> sockaddr type으로 구조체 형 변환함에 유의
	// bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen)
	bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));


	// 클라이언트에게 받은 메세지 돌려주기
	do{
		len = sizeof(cliaddr);
		n = recvfrom(sockfd, msg, 1000, 0, (struct sockaddr*)&cliaddr, &len);
		sendto(sockfd, msg, n, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));

		msg[n] = '\0'; // NULL
		printf("Received Message : %s", msg);

	}while(strncmp(msg, "q", 1));

	close(sockfd);

	return 0;
}


