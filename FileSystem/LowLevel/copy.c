#include <unistd.h> // for Unix System Call
#include <fcntl.h>  // for file setting or modifying
#include <stdio.h> // standard in out - perror()
#include <sys/types.h>
#include <sys/stat.h>

// file call -> with 2 argv 1. filename 2. copied filename

int main(int argc, char** argv)
{

	int n , in , out; // for file descriptor
	char buf[1024]; // for buffer

	if (argc < 3)
	{
		write(2, "Usage : copy file1 file2",25);  // 2 : stderr fd
		return -1;
	}

	// read file
	if ( (in = open(argv[1], O_RDONLY)) < 0 )
	{
		perror(argv[1]);
		return -1;
	}

	// open write file with create new file | erase existed file mode 
	// privailage : read and write to file owner 
	if ( (out = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR)) < 0 )
	{
		perror(argv[2]);
		return -1;
	}

	// read file and write file
	while ( (n = read(in, buf, sizeof(buf))) > 0 )
		write(out, buf, n);

	close(in);
	close(out);

	return 0;
}

