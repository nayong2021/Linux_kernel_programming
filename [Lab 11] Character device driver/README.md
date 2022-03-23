먼저 실행하기 위해 make명령을 이용해 컴파일 합니다.
그 다음 vm으로 linux를 부팅한 다음 my_cdev.ko kernel module이 있는 디렉토리로 와서

mknod /dev/mycdev c 42 0
insmod my_cdev.ko

위의 두 명령을 실행해 character device driver를 생성하고 모듈을 load한 다음
/dev/mycdev 경로를 이용해 cat명령을 실행하고, pipe를 이용해 echo를 이 경로에 하여
read, write를 수행합니다.

cat /dev/mycdev를 실행하면 default로는 hello가 출력되며 pipe를 이용한 echo로 
echo input > /dev/mycdev를 실행하면 input의 위치에 쓰인 문자열이 kernel영역의 buffer에 덮어씌워지며
다음에 cat 명령을 실행하면 마지막으로 echo로 입력한 문자열이 출력됩니다.
