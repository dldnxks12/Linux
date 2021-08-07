- File system call

    → Unix는 Directory나 device 모두 file로 취급하므로, 이 file을 잘 다룰 수 있어야한다.

    → 기본적인 5개의 기능을 사용할 줄 알아야한다.

        1. file 열기/생성 : open()
        2. file 읽기 : read()
        3. file 쓰기 : write()
        4. file 닫기 : close()
        5. file 설정 : fcntl() / ioctl()

    → Linux low-level file function
  
            - open() : file 열기
            - creat() : 빈 file 생성 → open으로 대체 가능
            - close() : 열린 file 닫기
            - read()  : 열린 file 읽기
            - write() : 열린 file 쓰기
            - lseek() : File Pointer 옮기기
            - unlink(): file 제거
            - remove() : file or directory 제거
            - fcntl() : file 관련 속성 설정
            - dup() : file descriptor 복사
