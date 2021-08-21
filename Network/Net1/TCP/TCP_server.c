#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define TCP_PORT 5100 // server의 port 번호

int main(int argc, char* argv[]){

  int ssock;       // socket descriptor
  socklen_t clen;  // addr 구조체 length
  int n;
  
  struct sockaddr_in servaddr, cliaddr;
  char msg[BUFSIZ];
  
  // Server Socket 생성
  if((ssock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    
      perror("socket()");
      return -1;
   }
  
  // Addr 구조체에 주소 지정 
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // 서버 자신의 IP 주소를 사용해야 하는데, INADDR_ANY flag를 사용하면 알아서 내 IP주소를 찾아서 할당해준다. 
  servaddr.sin_port = htons(TCP_PORT);
  
  // bind() 함수를 통해서 서버 소켓의 주소 설정
  if ( bind(ssock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){  
      perror("bind()");
      return -1;    
  }
  
  // 동시에 접속하는 클라이언트들을 위한 대기 Queue 생성 - listen()
  if( listen(ssock, 8) < 0){  
    perror("listen()");
    return -1;    
  }
  
  // cliaddr의 크기
  clen = sizeof(cliaddr);
  do{
    
    int n;    
    // 클라이언트가 접속하면 허용하고 (accept()) , 클라이언트 소켓 생성
    int csock = accept(ssock, (struct sockaddr)&cliaddr, &clen); // accept 될 때마다 csock 생성하고 , 끝나면 해당 소켓은 닫을 것 
    
    // 숫자 네트워크 주소를 문자열로 변환
    inet_ntop(AF_INET, &cliaddr.sin_addr, meg, BUFSIZ);
    printf("Client is Connected : %s\n", msg);
    
    if((n = read(csock, msg, BUFSIZ)) <= 0){    
      perror("read()");      
    }
    
    printf("Received Data : %s\n", msg);
    
    if(write(csock, msg, n) <= 0){    
      perror("write()");      
    }      
    close(csock);  
  }while(strncmp(msg, "q", 1));
  
  close(ssock);
  
  return 0;
}
