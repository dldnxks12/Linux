#### Command line arguments 

	int main(int argc, char* argv)에 대한 이해가 어느 정도 필요

	argvs는 문자열을 담은 배열을 가리키는 포인터

	다음의 그림들과 arg.c C source code를 이용해서 이해


![KakaoTalk_20210803_102829756](https://user-images.githubusercontent.com/59076451/127943423-9f7a5629-4f71-4a43-baf1-016c09d3ec62.jpg)

![111](https://user-images.githubusercontent.com/59076451/127943334-384b000e-9290-4d26-b451-09883c8a9b60.PNG)


#### exit(0), exit(1), return ?

	exit(0) : EXIT_SUCCESS - 정상 종료

	exit(1) : EXIT_FAILURE - 에러 메세지 종료

	return  : exit()과는 다르게 뒤의 문장을 수행한 후에 종료한다.

		일반 함수 내에서 return 사용시 해당 함수 종료 
	
		main() 함수 내에서 return 사용시 해당 프로세스를 종료


#### Option Parsing in C


	Linux의 대부분 명령어는 - 로 시작하는 실행 인자로 옵션을 지정할 수 있다!

		ex) ls -l , ls -al , ...

	옵션은 해당 명령어를 우리가 만들 때 정의한 것으로, Kernel or OS가 그 형태를 강제하지 않는다.

	추가적으로 '-' , '--' 인자가 다음의 의미를 갖는다.

		'-'  : 표준 입력에서 읽으라
		'--' : 이 이후의 인자는 옵션으로 해석되지 않는다. 

			-로 시작하는 문자열을 인자로 전달하고 싶을 때 사용한다.



	자세한 내용 : head_parser.c code 참조
