#include <stdio.h> // standard IO 를 위한 Header file


int main(int argc, char ** argv)
{

	int n;
	FILE *in, *out; // FILE 구조체
	char buf[BUFSIZ];

	if (argc != 3){
		fprintf(stderr, "Usage : fcopy file1 file2 \n"); // fprintf -> 출력 방향 정할 수 있다.
		return -1;
	}

	// fopen() : file pointer return
	if ((in = fopen(argv[1], "r")) == NULL )
	{
		perror(argv[1]);
		return -1;
	}
	if ( (out = fopen(argv[2],"w")) == NULL  )
	{
		perror(argv[2]);
		return -1;
	}

	// fwrie(), fread() 

	while ((n = fread(buf, sizeof(char),BUFSIZ, in )) > 0)
		fwrite(buf, sizeof(char), n, out);

	fclose(in);
	fclose(out);

	return 0;

}


