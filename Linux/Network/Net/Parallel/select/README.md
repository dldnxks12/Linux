#### I/O 멀티플랙싱 : select

I/O 멀티 플랙싱을 위한 대표적인 함수가 select()이다.

이 함수는 fd의 변화를 확인하는데, fd를 통해 데이터 송수신이 가능한 상태인지를 확인하는 것이다!

	이러한 변화를 감지해서 하나의 전송로를 동시에 여러 사용자가 사용할 수 있도록 효율성을 극대화한다.

		무슨 이야기 인지 잘 모르겠다면 code를 보며 이해해보자

