/* 
open()

# flags
0 O_RDONLY
1 O_WRONLY
2 O_RDWR

*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> // mode, flags 인자에 넣어줄 값들이 담긴 header 

int open(const char* path, int flags, /*, mode_t mode */); // 3 번 째 인자 mode는 file 생성 시 접근 권한을 설정할 수 있다. 
// file 열기에 성공하면 0보다 큰 file descriptor 반환 else -1 반환 

// creat()

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> // mode , flags 인자에 넣어줄 값들이 담긴 header 

int open(const char* path, mode_t mode); // 3 번 째 인자 mode는 file 생성 시 접근 권한을 설정할 수 있다. 
// open(path, O_WRONLY|O_CREAT|O_TRUNC, mode) 와 같은 기능 

#include <unistd.h> // maybe file descriptor에 대한 header file 

int close(int fd); // 해당 하는 file descriptor 제거
// 일반적으로 열린 file들은 close 함수를 통해 직접 닫아야한다.
// process kill에 의한 종료의 경우 모든 file들이 운영체제에 의해 자동으로 닫힌다.


// read()
// 열린 file descriptor를 이용해서 file로 부터 데이터를 읽어들임 , data를 읽은 만큼 file 내의 offset이 증가 
// fd : file descriptor , buf : 읽어 들인 데이터 저장하는 버퍼의 포인터형 변수 , count : 한 번에 읽어 들인 데이터 바이트 수 
// 읽어들인 바이트 수를 return 
#include <unistd.h>
ssize_t read(int fd, void* buf , size_t count);

// write()
// data를 쓴 만큼 offset 증가 , count : 한 번에 쓸 최대 Byte 수
#include <unistd.h>
ssize_t write(int fd, const void* buf, size_t count);

// lseek() 
// file pointer 이동
#include <sys/types.h>
#include <unistd.h>

off_t lseek(int fd, off_t offset, int whence);

// fcntl / ioctl 
// file의 성질 설정, 조정 

#include <unistd.h>
#include <fcntl.h>

int fcntl(int fd, int cmd, /* int arg */);
// 현재 fd 복사, fd 획득, file 상태 flag 설정 획득 등 다양한 기능 






