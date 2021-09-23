#include <time.h> // UNIX에서 시간을 우리가 알아 볼 수 있도록 하는 과정이 필요하기 때문에 아래와 같은 과정을 거쳐서 사용한다.
#include <stdio.h>

void delay(unsigned int sec)
{

	clock_t  ticks1 = clock();
	clock_t  ticks2 = ticks1;
	while( (ticks2 /CLOCKS_PER_SEC - ticks1 / CLOCKS_PER_SEC) < (clock_t)sec)
		ticks2 = clock();

}
int main(int argc, char* argv[])
{

	printf("helloworld\n");
	delay(3);
	printf("helloworld \n");
	return 0;
}
