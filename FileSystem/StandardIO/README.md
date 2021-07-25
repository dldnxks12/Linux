
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

fflush() 

-> 표준 입출력 라이브러리는 버퍼를 이용해서 stream IO를 수행 
이 때, 표준입력 stdin과 표준 출력 stdout은 buffer를 사용 but stderr는 buffer를 거치지 않고 바로 출력한다.

- 입력과 출력의 역할이 변경될 때 buffer를 비운다. 

ex) stdin에서 read할 때 출력 buffer가 비워진다.
ex) stdout에서 write할 때 입력 buffer가 비워진다.

강제적으로 buffer를 비우고자 할 때 fflush() 함수를 사용할 수 있다.
이 함수는 file stream의 모든 데이터를 즉시 출력한다. 일반적으로 출력 stream에 대해 동작한다.

#include <stdio.h>

int fflush(FILE *fp) 

-> 인자로 출력하고 싶은 stream을 명시하는데, NULL을 명시하면 모든 출력 stream에 대해 동작
	-> 성공 :0 , 실패 : EOF(-1) return 

fclose() 함수가 동작할 때 내부적으로 fflush() 함수가 호출되므로 별도로 fflush()를 call할 필요는 없다. 






