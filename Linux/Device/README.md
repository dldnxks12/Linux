### Device and Device Driver


#### 디바이스

	- 커널의 중요한 역할 중 하나가 컴퓨터의 HW를 관리하는 것이다. 다음과 같은 HW를 관리한다.

		CPU

		메모리

		HDD(hard disk drive)

		SSD(solid state drive)

		DVD-ROM 드라이브

		CD-ROM 드라이브 

		Graphic Adoptor (또는 Graphic Card) - 화면을 모니터에 전달

		Network Adoptor - 네트워크

		Sound Card - 소리

		시계 (HW Clock)

	위의 물리적인 부품을 디바이스라 한다. 커널은 위 드바이스들을 총괄한다. 

#### 디바이스 드라이버 

	HDD에도 여러 종류가 있다. 

	만약 종류가 다른 HDD가 3개 있다면, 커널은 각 HDD에 대응하는 Adopter 코드가 3개 필요!

	이렇게 특정 디바이스를 조작하는 SW를 디바이스 드라이버라 한다. 


#### 시스템 콜

	HW를 직접 다루는 건 Kernel만 할 수 있기 때문에 일반 프로그램은 HW를 사용하려면 Kernel에 요청을 해야한다.

	일반 프로그램이 커널에 디바이스 조작을 요청하려면 'System call'을 해야한다.

	여기서 System은 kernel을 의미한다. 
		
	
		
