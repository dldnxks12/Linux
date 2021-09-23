
#### malloc(3)


	malloc()은 size만큼의 바이트를 heap 영역에 할당하고, 그 첫 번째 주소에 대한 포인터를 반환한다.

	반환값의 타입은 void* 이기 때문에 형 변환을 필요로 한다. 

	할당될 메모리에 초기값을 지정하고 싶으면, memset() 또는 calloc()을 사용한다. 

	malloc()으로 확보한 메모리는 free()로 반드시 해제해야한다. - * 메모리 누수 원인 

		#include <stdlib.h>

		void* malloc(size_t size)  - * size_t : int type , ssize_t : unsigned int type in linux


	
#### calloc(3)

	calloc()은 nmemb x size 바이트의 메모리를 heap 영역에 할당하고, 그 첫 주소에 대한 포인터를 반환한다.

	malloc()과 달리 할당된 메모리는 초기값으로 0 이 설정된다.

		#include <stdlib.h>

		void* calloc(size_t nmemb, size_t size);

#### realloc(3)

	realloc()은 malloc()이나 calloc()으로 할당한 메모리 영역의 크기를 인자로 지정한 size 바이트로 확장 또는 축소한다

	경우에 따라 ptr이 가리키는 주소가 이동할 수 있는데, 이 경우 ptr의 내용이 복사된다.

	
		#include <stdlib.h>

		void* realloc(void *ptr, size_t size)


#### free(3)

	malloc(), calloc(), realloc()으로 heap 영역에 할당한 메모리 ptr을 해제한다.

	free()로 해제하면 그 메모리에 접근하면 안된다.

		! 항상 free()로 메모리를 해제해야하지만, exit() 함수를 사용한 경우는 예외이다.

		exit()을 사용하면 그 프로세스의 메로리 공간이 모두 소멸해 버리기 때문이다





	

		


