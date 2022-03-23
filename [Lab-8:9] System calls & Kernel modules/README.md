코드는 모두 src디렉토리의 하위 폴더들에 저장되어 있습니다. 테스트를 진행하기 전에
먼저 src디렉토리의 하위폴더 setting에서 make명령어를 통해 syscall_64.tbl등 system call셋팅을 위한 파일들을 변경해줄 수 있습니다. 
이것이 가능하도록 하기 위해선 201720707_sce394_lab8_9 폴더가 kernel-utils/labs폴더에 위치해야 합니다.

만약 linux버전이 다르거나 하는 등의 이유로 문제가 발생할 수 있으면 
src/user-space_test/prime_syscall폴더의 파일들을 kernel-utils/src/linux-5.15.4폴더에 prime_syscall폴더를 생성한 후 복사하고
linux-5.15.4/Makefile에 core-y += 항목에 /prime_syscall 항목을 추가하고 syscall_64.tbl에
548	64	prime_syscall		sys_prime_syscall
줄을 추가하고
include/linux/syscalls.h 파일에
asmlinkage long sys_prime_syscall(void);
줄을 추가해 사전 설정을 마무리 합니다.

그 후 user-space, user-space_test, kernel_module 폴더 각각에서 make 명령어로 컴파일을 완료한 수 linux-5.15.4폴더에서 make -j$(nproc)로 커널을 생성한 다음 커널을 실행해 테스트를 합니다.
각 폴더에 생성된 prime_user, prime_sys_test, prime_module.ko파일을 과제 안내 ppt의 execution examples와 같은 방법으로 실행할 수 있습니다.
