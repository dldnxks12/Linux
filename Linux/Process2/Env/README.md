#### Environment Variable

	환경 변수는 프로세스의 부모/자식 관계를 통해서 전파되는 전역 변수와 같은 것이다. 

	보통 항상 설정해두고 싶은 값을 프로그램에 전달하기 위해 사용한다. 

		ex) 환경 변수 LESS에 "-i"를 설정해두면, less는 항상 "-i" 옵션으로 실행된다 !!

		이와 비슷한 환경 변수로 MORE, GZIP 등이 있다.

		
		만약 she = love 라고 정하고 싶다면?

			export she="love" 를 쉘에서 실행한다.

			echo $she 를 실행하면 love가 출력 된다!

		만약 위 변수가 계속 유지되도록 전역 설정하려면 어떡하나?

			이는 $/HOME/.bashrc file에 해당 스크립트를 입력하면 된다.

			($HOME = /home/usr)

			echo 'export she="love"' >> ~/.bashrc
