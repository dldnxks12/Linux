#include <unistd.h> // header for Unix System Call
#include <stdio.h>  // header for stdin stdout stderr
#include <string.h> // header for string 
#include <fcntl.h>  // header for file attribute setting
#include <dirent.h> // header for directory attribute setting
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/stat.h> // header for file information
#include <sys/types.h>


// main(int argc, char* argv[]) -> char* argv[] = "I love you" , argv[1] = I , ...
// argv 는 문자열의 배열을 받음  argv[1] == 문자열 , argv[2] == 문자열 
// 따라서 문자열의 배열을 받는 것이므로 이중 포인터를 사용  (문자열을 가리키는 포인터 배열로 이해해도 된다.)

int list(char *arg)
{
	DIR *pdir; // DIR 구조체 alias 사용으로 struct keyword 생략 -> directory 조작을 위한 구조체 포인터 선언
	struct dirent *dirt; // directory 항목을 위한 구조체 포인터 선언 -> 역참조 또는 '->' 연산자를 통해 접근
	struct stat statbuf ; // file 정보를 위한 구조체 변수 선언 -> 바로 접근
	struct passwd *username; // 사용자 이름 출력을 위한 구조체 포인터 선언
	struct group *groupname; // 그룹 이름 출력을 위한 구조체 포인터 선언
	struct tm *t // 시간출력을 위한 구조체 포인터 선언

	// why 구조체 포인터 ?
	


}

int main(int argc, char* argv[]) // argv는 문자열을 가리키는 포인터를 담은 배열
{}
