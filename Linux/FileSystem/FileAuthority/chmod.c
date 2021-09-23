#include <sys/stat.h> // file 정보에 대한 header file
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	struct stat statbuf; // file 정보에 대한 구조체 

	if (argc < 3)
	{
		fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
		return -1;
	}

	// file 이 존재하는지 
	if (stat(argv[1], &statbuf) < 0) // argv[1] file에 대한 정보를 statbuf에 담아서 return
	{
		perror("stat");
		return -1;
	}

	// group id를 설정 하고 group의 실행 권한 해제

	if(chmod(argv[1], (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
	{
		perror("chmod");
		return -1;
	}

	// file 권한을 644로 설정

	if(chmod(argv[2], S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH) < 0)
	{
		perror("chmod");
		return -1;
	}

	return 0;

}
