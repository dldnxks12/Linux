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

int listDir(char *arg) // char *arg  = argv[1] 즉, 문자열(filename or file path)을 넘겨줌
{
	DIR *pdir; // DIR 구조체 alias 사용으로 struct keyword 생략 -> directory 조작을 위한 구조체 포인터 선언
	struct dirent *dirt; // directory 항목을 위한 구조체 포인터 선언 -> 역참조 또는 '->' 연산자를 통해 접근
	struct stat statbuf ; // file 정보를 위한 구조체 변수 선언 -> 바로 접근
	struct passwd *username; // 사용자 이름 출력을 위한 구조체 포인터 선언
	struct group *groupname; // 그룹 이름 출력을 위한 구조체 포인터 선언
	struct tm *t // 시간출력을 위한 구조체 포인터 선언

	int i = 0;
	int count = 0;

	// dirname : 문자열들의 배열이기 때문에 이중포인터 사용
	char *dirName[255]; // 255 크기의 배열의 시작 주소를 가리키는 포인터. 즉 포인터를 가리키는 포인터
	char buf[255];
	char permission[1];
	char mtime[20];

	// memset(메모리 주소, 초기화할 데이터, 크기) -> 메모리 초기화
	memset(dirName, 0, sizeof(dirName)); // dirName이 담고 있는 주소들을 초기화 -> 배열이니까 이름 그대로 넘겨줌
	memset(&dirt, 0, sizeof(dirt)); // dirent 구조체 포인터의 메모리 주소 &dirt로 넘겨줌
	memset(&statbuf, 0 , sizeof(statbuf)); // stat 구조체의 주소를 넘겨줌

	if((pdir = opendir(arg)) <=0) // opendir(const char *path) -> file 이름 넘겨줄 것
	{
		perror("opendir");
		return -1;
	}

	chdir(arg); // 해당 directory로 이동
	getcwd(buf, 255); // 현재 directory의 절대 경로를 가져와서 표시
	printf("\n%s: directory\n", arg); // 즉, arg file이 있는 directory로 이동해서 현재 경로를 표시

	// directory를 재귀적으로 호출하며 현재 경로에 존재하는 directory들을 모두 표시
	while((dirt = readdir(pdir)) != NULL ) // readdir()은 구조체를 return 정확히는 구조체를 가리키는 포인터를 return
	{
		lstat(dirt -> d_name, &statbuf); // 현재 directory에 대한 내용을 statbuf에 저장해서 return
		// file type check
		if(S_ISDIR(statbuf.st_mode))
			permission[0] = 'd';
		else if(S_ISLNK(statbuf.st_mode))
			permission[0] = 'l';
		else if(S_ISCHR(statbuf.st_mode))
			permission[0] = 'c';
		else if(S_ISBLK(statbuf.st_mode))
			permission[0] = 'b';
		else if(S_ISSOCK(statbuf.st_mode))
			permission[0] = 's';
		else if(S_ISFIFO(statbuf.st_mode))
			permission[0] = 'P';
		else
			permission[0] = '-';

		// user authority check
		permission[1] = statbuf.st_mode&S_IRUSR? 'r' : '-'; // S_IRUSR이면 r 아니면 -
		permission[2] = statbuf.st_mode&S_IWUSR? 'w' : '-';
		permission[3] = statbuf.st_mode&S_IXUSR? 'x' :
			        statbuf.st_mode&S_IRUID? 'S' : '-';

		// group authority check
		permission[4] = statbuf.st_mode&S_IRGRP? 'r' : '-';
		permission[5] = statbuf.st_mode&S_IWGRP? 'w' : '-';
		permission[6] = statbuf.st_mode&S_IXGRP? 'x' :
			        statbuf.st_mode&S_ISGID? 'S' : '-';
		// others authority check
		permission[7] = statbuf.st_mode&S_IROTH? 'r' : '-';
		permission[8] = statbuf.st_mode&S_IWOTH? 'w' : '-';
		permission[9] = statbuf.st_mode&S_IXOTH? 'x' : '-';

		if (statbuf.st_mode & S_IXOTH) // 스티키 비트 설정 
		{
			permission[9] = statbuf.st_mode&S_ISVTX? 't' : 'x';

		}else{
			permission[9] = statbuf.st_mode&S_ISVTX? 'T' : '-';
		}

		permission[10] = '\0'

	}


	if(S_ISDIR(statbuf.st_mode) == 1 ) // 디렉토리?
	{
		if(strcmp(dirt->d_name, ".") && strcmp(dirt->d_name, "..") )
		{
			dirName[count] = dirt->d_name;
			count = count+1;
		}
	}

	username = getpwuid(statbuf.st_uid);
	groupname = getgrgid(statbuf.st_gid);
	t = localtime(&statbuf.st_mtime);

	sprintf(mtime, "%04d-%02d-%02d %02d:%02d:%02d",
		t->tm_year+1900, t->tm_mon +1, t->tm.mday,
		t->tm_hour, t->tm_min, t->tm_sec);

	printf("%s %2d %s %s %9ld %s %s\n", permission, statbuf.st_nlink, username->pw_name, groupname->gr_name, 
		statbuf.st_size, mtime, dirt->d_name);

	for(i =0; i<count; i++)
	{
		if(listDir(dirName[i] == -1))
			break;
	}

	printf("\n");
	closedir(pdir);
	chdir("..");

	return 0;
}

int main(int argc, char* argv[]) // argv는 문자열을 가리키는 포인터를 담은 배열
{
	if(argc <2)
	{
		fprintf(stderr, "UsageL %s directory_name. \n", argv[0]);
		return -1;
	}

	listDir(argv[1]);

	return 0;
}
