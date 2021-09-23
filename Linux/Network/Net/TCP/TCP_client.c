#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define TCP_PORT 5100

int main(int argc, char* argv[]){

  int ssock;
  struct sockaddr_in servaddr; // server addr 구조체만 선언 
  char msg[BUFSIZ];
  
  if(argc < 2){
    printf("Usage : %s IP Address \n", argv[0]);
    return -1;
  }
  
  // Socket 생성
  if( (ssock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    perror("socket()");
    return -1;
  }
  
  // socket이 접속할 주소 지정
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;  
  // argv[1] : 연결할 서버의 IP 주소 
  inet_pton(AF_INET, argv[1], &(servaddr.sin_addr.s_addr));
  servaddr.sin_port = htons(TCP_PORT);
  
  // 지정한 주소로 접속 !  - connect(0
  if(connect(ssock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){  
    perror("connect()");
    return -1;
  }
  
  // 키보드에서 문자열 입력 받기
  fgets(msg, BUFSIZ, stdin); 
  if(send(ssock, msg, BUFSIZ, MSG_DONTWAIT) <= 0){   // 데이터를 소켓에 쓰기
    perror("send");
    return -1;    
  }
  
  memset(msg, 0, BUFSIZ); // msg buffer 비우기
  if(recv(ssock, msg, BUFSIZ, 0) <= 0){ // 소켓으로 부터 데이터를 읽기 
    perror("recv()");
    return -1;
  }
  
  printf("Received Data : %s\n", msg);
  
  close(ssock);
  
  return 0;
}
