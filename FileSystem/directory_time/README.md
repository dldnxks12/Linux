

### 포인터, 매개변수 부분 잘 신경쓰기


int main(int argc, char **argv)

	-> char **argv == char *argv 
		-> CLI에서 두 번째 인자로 file들을 넘겨준다.
		-> C에서 문자열은 Pointer 변수에 저장하여 사용한다.
		-> 즉 , argv는 문자열들의 배열을 받는다.
		
	ex) char **argv 에 file1 file2 file3 넘겨준다면
		argv[0] = file1
		argv[1] = file2
		argv[2] = file3 

		여기서 file1, file2, file3는 string이므로, 이 string들을 모두 배열로 넘겨주게 된다.

		char **argv = {file1, file2, file3}

### tag

Linux OS에서 structure를 typedef를 이용하여 alias로 사용하는 경우에 이를 구별할 수 있도록 하기 위해 tag를 사용한다.

보통 typedef struct person{}tag_person; 로 사용하거나, typedef struct person{}person_t; 로 사용한다.

Linux의 struct 설명을 보면 

{
	Node_t iNode;
	Person_t person;
}

과 같이 사용하는 것을 확인할 수 있다. 즉, _t가 붙어있으면 alias로 사용되는 구조체로 보면 된다. 

