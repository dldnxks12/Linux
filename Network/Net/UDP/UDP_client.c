// 프로그램을 실행할 때 서버의 주소를 입력해야한다.
// 입력받은 문자는 inet_pton() 함수를 써서 16진수 숫자 주소로 변환할 수 있다.


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define UDP_PORT 5100

int main(int argc, char*argv[]){

	int sockfd; // socket descriptor
	int n;

	struct sockaddr_in servaddr, cliaddr;
	socklen_t clisize;
	char msg[BUFSIZ];


	if(argc !=2){
		printf("Usage : %s <IP Address> \n", argv[0]);
		return -1;
	}

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	// 서버의 IP 주소와 Port 번호를 이용해서 주소 설정
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	// IP 문자열을 16진수 숫자 주소로 변경 - servaddr.sin_addr.s_addr setting
	inet_pton(AF_INET, argv[1], &(servaddr.sin_addr.s_addr));
	servaddr.sin_port = htons(UDP_PORT);

	// 키보드에서 문자열을 입력받아 서버로 전송
	do{

		fgets(msg, BUFSIZ, stdin); // enter가 눌리기 전까지 쭉 읽다가 msg에 담기
		sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
		clisize = sizeof(cliaddr);


		// 서버에서 데이터 받아서 화면에 출력

		n = recvfrom(sockfd, msg, BUFSIZ, 0 , (struct sockaddr*)&cliaddr, &clisize);
		fputs(msg, stdout);
	}while(strncmp(msg, "q", 1));

	close(sockfd);

	return 0;
}
