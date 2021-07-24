
// open()

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> // flags 인자에 넣어줄 값들이 담긴 header 

/*

# flags

0 O_RDONLY
1 O_WRONLY
2 O_RDWR

*/

int open(const char* path, int flags, /*, mode_t mode */); // 3 번 째 인자 mode는 file 생성 시 접근 권한을 설정할 수 있다. 
