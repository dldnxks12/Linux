### Linux Programming Directory


- 참고서적

		Linux Programming with Raspberry Pi

		모두를 위한 리눅스 프로그래밍 - 아오키 미네로 


#### OS Call ?

	- System Call

		컴퓨터 시스템에는 Kernel Mode, User Mode의 두 가지 모드가 존재 

			Kernel Mode에서 프로그램은 메모리 및 하드웨어 자원에 직접 접근 가능
	
			User Mode에서 프로그램은 메모리 및 하드웨어 자원에 직접 접근 불가능

		대부분의 프로그램은 User Mode에서 실행된다. 하지만 프로그램의 실행 과정 중 메모리나 하드웨어 자원이 필요한 경우,
	
		System Call을 사용해서 Kernel에 도움(요청)을 보낸다. 


			User mode -> kernel mode -> 작업 완료 -> Kernel mode -> User mode

		위와 같은 모드 전환을 Context Switching이라 한다.



	- Library Call 

		Library Call은 프로그래밍 라이브러리에서 제공하는 기능을 사용하도록 요청한다.

		개발자가 특정 Library Call을 사용하는 경우, 먼저 관련 라이브러리를 가져와야한다.

		C에서는 header file을 include 하는 방식(전처리 지시문 - #include)으로 해당 라이브러리를 가져온다. 

		



	- System Call , Library Call의 차이

		System Call  : 자원에 접근하기 위해서 Kernel mode로 들어가기 위한 요청을 kernel에 요청하는 것

		Library Call : 프로그램이 프로그래밍 라이브러리에 정의된 기능에 접근하기 위한 요청 



	- read() / write  , fread() / fwrite() 비교

		Library Call을 사용하더라도 내부적으로 System Call을 사용한다.

		그럼 어떤 차이가 있는가?

		fread, fwrite는 내부적으로 buffer에 데이터를 쌓았다가 일정량이상 되면 read()/write()를 Call 한다.

		즉, System Call의 호출 빈도를 조절할 수 있다. 

		

		

		
