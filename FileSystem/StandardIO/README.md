
### Standard IO  <stdio.h>

표준 입출력 함수에서 데이터는 Stream으로 취급한다.
프로세스를 생성하면 자동으로 stdin, stdout, stderr가 연결된다. (fd : 0 1 2)

- 표준 입출력 
	stdin  : scanf
	stdout : printf
	stderr : perror

- printf, fprintf, sprintf 차이

printf  : 서식화된 문자열을 표준 출력(stdout)에 보내는 것 
	int printf(const char *format-string, argument-list)
fprintf : file stream에 서식화된 문자열을 출력 
	int fprintf(FILE *stream, const char *format-string, argument-list)
		즉, stdout으로 출력을 내보낼 수 있고, 특정 file에 출력을 내보낼 수도 있다. (ex 메모장)
sprintf : 배열로 이러우진 버퍼에 일련의 서식 문자열을 입력하는 함수. 즉, file이나 모니터가 아니라 버퍼에 문자열을 출력
	int sprintf(char[] buffer, const char *format-string, argument-list);

	sprintf(string, "hello world. My name is %s", "종수");
	printf("%s",string);
		-> hello world. My name is 종수 출력 
			

**참고 (문자열과 sprintf)

	string이라는 문자열이 따로 있는 C++과 달리 C는 모든 문자, 문자열을 char형으로 처리한다.
	즉, 문자는 char, 문자열은 char* or char[]을 이용하여 string.h header를 통해 처리한다.
	문자열 상수는 한 번 선언되면 새로 할당하는 것 말고는 내용을 변경할 수 없다.
	따라서 배열로 선언된 char type 문자열을 주로 사용하는데, 이 문자열에 서식화된 문자열을 할당할 수 있는 함수가 sprintf이다.
		string.h header에 있는 strcpy를 통해 배열에 문자열을 할당할 수 있지만, 서식화되어있지 않다.
		서식화를 위해서는 sprintf를 통해 배열에 문자열을 할당하면 된다.
			( 서식화? 사용자가 정의한 형식에 따라 화면에 출력되는 정보. %d:10진수 등..)

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


- 그 외 Stdio의 함수 

![222](https://user-images.githubusercontent.com/59076451/126884992-ed5fe3b3-dc40-4bdc-be33-9b73659a947e.jpg)




