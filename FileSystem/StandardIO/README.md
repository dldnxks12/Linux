
### Standard IO  <stdio.h>

표준 입출력 함수에서 데이터는 Stream으로 취급한다.
프로세스를 생성하면 자동으로 stdin, stdout, stderr가 연결된다. (fd : 0 1 2)

C에서 이 Stream은 FILE Structure의 file pointer를 통해 다룰 수 있다.
FILE Structure는 <stdio.h>에 정의되어있다.

typedef struct{
	int _cnt;
	char *_ptr;
	char *_base;
	char _flag;
	char _file;
}FILE;

저수준 입출력을 위해 open(), read(), write() 함수가 존재했 듯, 표준 입출력 라이브러리에도 비슷한 함수가 존재
fopen(), fread(), fwrite(0, fclose()로 data stream을 다룰 수 있다.
fopen()을 통해 stream을 열면 file structure의 file pointer가 반환된다.

fopen() 함수는 내부적으로 FILE structure의 각 field를 초기화 한 후 open() 를 call한다.

